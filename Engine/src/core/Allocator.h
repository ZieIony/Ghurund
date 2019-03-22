#pragma once

#include "Ghurund.h"
#include "Buffer.h"
#include "collection/List.h"

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

    class AllocationStrategy {
    protected:
        memory_t size;
        memory_t alignAddress, alignSize;

    public:
        virtual ~AllocationStrategy() {}

        void init(memory_t size, memory_t alignAddress = 1, memory_t alignSize = 1) {
            this->size = std::max<>(size, alignSize);
            this->alignAddress = alignAddress;
            this->alignSize = alignSize;
        }

        virtual memory_t allocate(memory_t size) = 0;
        virtual void deallocate(memory_t) = 0;

        memory_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) memory_t Size;

        virtual memory_t getAllocated() const = 0;

        __declspec(property(get = getAllocated)) memory_t Allocated;
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

    class CircularBufferStrategy:public AllocationStrategy {
    private:
        memory_t start = 0, end = 0;
        List<Allocation> allocations;
        memory_t allocated = 0;

    public:
        CircularBufferStrategy() {
            start = 0;
            end = 0;
        }

        inline memory_t allocate(memory_t size) {
            memory_t newStart = align<>(end, alignAddress);
            memory_t alignedSize = align<>(size, alignSize);
            if (newStart + alignedSize > this->size)
                newStart = end = 0;
            if (allocated > 0 && end <= start && end + alignedSize > start)
                return this->size; // not enough memory in this buffer
            Allocation a = {alignedSize, newStart};
            allocations.add(a);
            end = newStart + alignedSize;
            allocated += alignedSize;
            return newStart;
        }

        inline void deallocate(memory_t address) {
            for (size_t i = 0; i < allocations.Size; i++) {
                Allocation& a = allocations[i];
                if (a.address == address) {
                    allocated -= a.size;
                    allocations.removeAtKeepOrder(i);
                    if (allocations.Size > 0) {
                        start = allocations[0].address;
                    } else {
                        start = end = 0;
                    }
                    return;
                }
            }
        }

        virtual memory_t getAllocated() const override {
            return start < end ? end - start : size - start + end;
        }
    };

    class PoolAllocator:public Allocator<void*> {
    private:
        Buffer* pool;
        AllocationStrategy* strategy;

    public:
        PoolAllocator(memory_t size, AllocationStrategy* strategy = nullptr) {
            this->strategy = strategy == nullptr ? ghnew CircularBufferStrategy() : strategy;
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