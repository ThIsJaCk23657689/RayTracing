#include "Utility/Console.hpp"
#include <cstdarg>
#include <iostream>

void Console::Print(const char* format, ...) {
    char buffer[1024];

    va_list args;
    va_start(args, format);

    int length = vsnprintf(buffer, sizeof(buffer), format, args);

    // if the buffer is not enough, use heap memory
    if (length >= sizeof(buffer)) {
        char* heap_buffer = new char[length + 1];
        vsnprintf(heap_buffer, length + 1, format, args);
        std::cout << heap_buffer << std::endl;
        delete[] heap_buffer;
    } else {
        std::cout << buffer << std::endl;
    }

    va_end(args);
}