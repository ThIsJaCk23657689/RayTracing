#include "Utility/Timer.hpp"
#include <cmath>
#include <iostream>

Timer::Timer() : m_is_ready_to_print(false) {}

void Timer::Start() {
    m_is_ready_to_print = false;
    m_start = chr::steady_clock::now();
}

void Timer::End() {
    m_end = chr::steady_clock::now();
    m_is_ready_to_print = true;
}

void Timer::Print(const std::string& message) {
    End();
    m_delta = m_end - m_start;
    if (m_is_ready_to_print) {
        std::cout << message << ", total time consuming: " + ShowDelta() << std::endl;
    } else {
        std::cerr << "[Error] Timer is not ready to print!" << std::endl;
    }
}

std::string Timer::ShowDelta() const {
    if (m_delta.count() >= 60.0f) {
        auto min = static_cast<int>(std::round(m_delta.count() / 60.0));
        auto sec = static_cast<int>(m_delta.count()) % 60;
        return std::to_string(min) + " minute(s) " + std::to_string(sec) + " second(s).";
    } else {
        return std::to_string(m_delta.count()) + " second(s).";
    }
}