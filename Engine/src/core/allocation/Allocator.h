#pragma once

#include "Ghurund.h"
#include "core/Buffer.h"
#include "collection/List.h"
#include "core/Logger.h"

namespace Ghurund {
    typedef UINT64 memory_t;

    template<class Type>
    __interface Allocator {
        Type allocate(memory_t size);
        void deallocate(Type);
    };

    struct Allocation {
        memory_t size;
        memory_t address;
    };

    class SimpleAllocator:public Allocator<void*> {
    public:
        inline void* allocate(memory_t size) {
            return operator new((size_t)size, _NORMAL_BLOCK, __FILE__, __LINE__);
        }

        inline void deallocate(void* obj) {
            operator delete(obj);
        }
    };
}