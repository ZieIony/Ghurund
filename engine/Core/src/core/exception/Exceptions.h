#pragma once

#include <exception>

namespace Ghurund::Core {
    class CallFailedException:public std::exception {
    public:
        CallFailedException(const char* message = nullptr):std::exception(message) {}
    };

    class NotImplementedException:public std::exception {};

    // TODO: this is questionable - it would be better if resources didn't have save(..) methods
    class NotSupportedException:public std::exception {};

    class InvalidDataException:public std::exception {
    public:
        InvalidDataException(const char* message = nullptr):std::exception(message) {}
    };

    class InvalidFormatException:public std::exception {
    public:
        InvalidFormatException(const char* message = nullptr):std::exception(message) {}
    };

    class InvalidStateException:public std::exception {
    public:
        InvalidStateException(const char* message = nullptr):std::exception(message) {}
    };

    class InvalidParamException:public std::exception {
    public:
        InvalidParamException(const char* message = nullptr):std::exception(message) {}
    };

    class IOException:public std::exception {
    public:
        IOException(const char* message = nullptr):std::exception(message) {}
    };

    class CloningNotSupportedException:public std::exception {};
}