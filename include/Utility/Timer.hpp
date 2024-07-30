#ifndef RAY_TRACING_TIMER_HPP
#define RAY_TRACING_TIMER_HPP

#include <chrono>
#include <string>

namespace chr = std::chrono;

struct Timer {
    chr::time_point<chr::steady_clock> m_start;
    chr::time_point<chr::steady_clock> m_end;
    chr::duration<double> m_delta;
    bool m_is_ready_to_print;

    Timer();
    void Start();
    void Print(const std::string& message);

private:
    void End();
    std::string ShowDelta() const;

};

#endif