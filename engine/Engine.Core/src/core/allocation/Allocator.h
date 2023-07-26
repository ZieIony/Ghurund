#pragma once

#include <exception>

namespace Ghurund::Core {
    class Allocator {
    public:
        virtual ~Allocator() = 0 {};

        virtual void* allocate(size_t size) = 0;

        virtual void deallocate(void*) = 0;

        virtual bool canAllocate(size_t size) const = 0;
    };

    struct Allocation {
        size_t size;
        size_t address;
    };

    class IncompatibleAllocatorsException:public std::exception {
    public:
        IncompatibleAllocatorsException(const char* message = nullptr):std::exception(message) {}
    };
}

inline void* operator new(size_t size, Ghurund::Core::Allocator& allocator) {
    return allocator.allocate(size);
}

inline void operator delete(void* ptr, Ghurund::Core::Allocator& allocator) {
    allocator.deallocate(ptr);
}