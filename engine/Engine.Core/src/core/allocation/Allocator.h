#pragma once

#include <exception>

namespace Ghurund::Core {
    __interface Allocator {
        void* allocate(size_t size);
        void deallocate(void*);
        bool canAllocate(size_t size) const;
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