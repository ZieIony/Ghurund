#pragma once

#include "SimpleBufferStrategy.h"

namespace Ghurund::Core {
    template<typename MemoryType>
    class PoolAllocator:public Allocator {
    private:
        Buffer* pool;
        AllocationStrategy* strategy;

    public:
        PoolAllocator(MemoryType size, AllocationStrategy* strategy = nullptr) {
            this->strategy = strategy == nullptr ? ghnew SimpleBufferStrategy() : strategy;
            this->strategy->init(size);
            pool = ghnew Buffer((size_t)size);
        }

        ~PoolAllocator() {
            delete strategy;
            delete[] pool;
        }

        inline void* allocate(MemoryType size) {
            MemoryType address = strategy->allocate(size);
            if (address == strategy->Size)
                return nullptr;
            return pool->Data + address;
        }

        inline void deallocate(void* obj) {
            strategy->deallocate((BYTE*)obj - pool->Data);
        }

		inline bool canAllocate(MemoryType size) const {
			return strategy->canAllocate(size);
		}
    };
}