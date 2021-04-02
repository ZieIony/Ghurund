#pragma once

namespace Ghurund {
    typedef uint64_t memory_t;

    __interface Allocator {
        void* allocate(memory_t size);
        void deallocate(void*);
        bool canAllocate(memory_t size) const;
    };

    struct Allocation {
        memory_t size;
        memory_t address;
    };
}

inline void* operator new(size_t size, Ghurund::Allocator& allocator) {
    return allocator.allocate(size);
}

inline void operator delete(void* ptr, Ghurund::Allocator& allocator) {
    allocator.deallocate(ptr);
}