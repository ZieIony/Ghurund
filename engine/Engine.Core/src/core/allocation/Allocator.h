#pragma once

namespace Ghurund::Core {
    template<typename T>
    __interface Allocator {
        void* allocate(T size);
        void deallocate(void*);
        bool canAllocate(T size) const;
    };

    template<typename T>
    struct Allocation {
        T size;
        T address;
    };
}

template<typename T>
inline void* operator new(size_t size, Ghurund::Core::Allocator<T>& allocator) {
    return allocator.allocate(size);
}

template<typename T>
inline void operator delete(void* ptr, Ghurund::Core::Allocator<T>& allocator) {
    allocator.deallocate(ptr);
}