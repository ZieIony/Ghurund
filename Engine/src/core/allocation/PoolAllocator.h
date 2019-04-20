#pragma once

#include "SimpleBufferStrategy.h"

namespace Ghurund {
    class PoolAllocator:public Allocator<void*> {
    private:
        Buffer* pool;
        AllocationStrategy* strategy;

    public:
        PoolAllocator(memory_t size, AllocationStrategy* strategy = nullptr) {
            this->strategy = strategy == nullptr ? ghnew SimpleBufferStrategy() : strategy;
            this->strategy->init(size);
            pool = ghnew Buffer((size_t)size);
        }

        ~PoolAllocator() {
            delete strategy;
            delete[] pool;
        }

        inline void* allocate(memory_t size) {
            memory_t address = strategy->allocate(size);
            if (address == strategy->Size)
                return nullptr;
            return pool->Data + address;
        }

        inline void deallocate(void* obj) {
            strategy->deallocate((BYTE*)obj - pool->Data);
        }
    };
}