#pragma once

#include <exception>

namespace Ghurund::Core {
    class OperationNotSupportedException:public std::exception {
    public:
        OperationNotSupportedException(const char* message = nullptr):std::exception(message) {}
    };
}