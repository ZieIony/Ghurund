#pragma once

#include "Allocator.h"

namespace Ghurund {
    class SimpleAllocator:public Allocator {
    public:
        SimpleAllocator() {}

        SimpleAllocator(const SimpleAllocator& a) {}

        SimpleAllocator(SimpleAllocator&& a) noexcept {}

        SimpleAllocator& operator=(const SimpleAllocator& other) {
            return *this;
        }

        SimpleAllocator& operator=(SimpleAllocator&& other) noexcept {
            return *this;
        }

        inline void* allocate(memory_t size) {
#ifdef _DEBUG
            return operator new((size_t)size, _NORMAL_BLOCK, __FILE__, __LINE__);
#else
            return operator new((size_t)size);
#endif
        }

        inline void deallocate(void* obj) {
            operator delete(obj);
        }

        inline bool canAllocate(memory_t size) const {
            return true;
        }
    };
}
