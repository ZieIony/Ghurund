#pragma once

#include <exception>

namespace Ghurund::Core {
    class CallFailedException:public std::exception {
    public:
        CallFailedException(const char* message = nullptr):std::exception(message) {}
    };

    class NotImplementedException:public std::exception {};

    class InvalidDataException:public std::exception {
    public:
        InvalidDataException(const char* message = nullptr):std::exception(message) {}
    };

    class InvalidStateException:public std::exception {
    public:
        InvalidStateException(const char* message = nullptr):std::exception(message) {}
    };

    class InvalidParamException:public std::exception {
    public:
        InvalidParamException(const char* message = nullptr):std::exception(message) {}
    };
}