#pragma once

#include "core/Buffer.h"
#include "core/collection/List.h"
#include "application/Logger.h"

namespace Ghurund {
    typedef UINT64 memory_t;

    __interface Allocator {
        void* allocate(memory_t size);
        void deallocate(void*);
		bool canAllocate(memory_t size) const;
    };

    struct Allocation {
        memory_t size;
        memory_t address;
    };

    class SimpleAllocator:public Allocator {
    public:
        inline void* allocate(memory_t size) {
            return operator new((size_t)size, _NORMAL_BLOCK, __FILE__, __LINE__);
        }

        inline void deallocate(void* obj) {
            operator delete(obj);
        }

		inline bool canAllocate(memory_t size) const {
			return true;
		}
	};
}

inline void* operator new(size_t size, Ghurund::Allocator& allocator) {
    return allocator.allocate(size);
}

inline void operator delete(void* ptr, Ghurund::Allocator& allocator) {
    allocator.deallocate(ptr);
}