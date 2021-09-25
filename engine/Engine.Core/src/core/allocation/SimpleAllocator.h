#pragma once

#include "Allocator.h"

namespace Ghurund::Core {
    class SimpleAllocator:public Allocator<size_t> {
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

        inline void* allocate(size_t size) {
#ifdef _DEBUG
            return operator new(size, _NORMAL_BLOCK, __FILE__, __LINE__);
#else
            return operator new(size);
#endif
        }

        inline void deallocate(void* obj) {
            operator delete(obj);
        }

        inline bool canAllocate(size_t size) const {
            return true;
        }
    };
}
