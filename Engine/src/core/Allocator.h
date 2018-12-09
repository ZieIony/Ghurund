#pragma once

#include "Ghurund.h"

namespace Ghurund {
    __interface Allocator {
        void *allocate(size_t size);
        void deallocate(void *);
    };

    class SimpleAllocator:public Allocator {
    public:
        inline void *allocate(size_t size) {
            return operator new(size, _NORMAL_BLOCK, __FILE__, __LINE__);
        }

        inline void deallocate(void *obj) {
            operator delete(obj);
        }
    };

    class PoolAllocator:public Allocator {

    };
}