#pragma once

#include "SimpleBufferStrategy.h"
#include "core/Buffer.h"

namespace Ghurund::Core {
    class PoolAllocator:public Allocator {
    private:
        Buffer* pool;
        AllocationStrategy* strategy;

    public:
        PoolAllocator(size_t size, AllocationStrategy* strategy = nullptr) {
            this->strategy = strategy == nullptr ? ghnew SimpleBufferStrategy() : strategy;
            this->strategy->init(size);
            pool = ghnew Buffer((size_t)size);
        }

        ~PoolAllocator() {
            delete strategy;
            delete[] pool;
        }

        inline void* allocate(size_t size) {
            size_t address = strategy->allocate(size);
            if (address == strategy->Size)
                return nullptr;
            return pool->Data + address;
        }

        inline void deallocate(void* obj) {
            strategy->deallocate((uint8_t*)obj - pool->Data);
        }

		inline bool canAllocate(size_t size) const {
			return strategy->canAllocate(size);
		}
    };
}