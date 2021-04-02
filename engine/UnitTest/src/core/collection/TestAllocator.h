#pragma once

#include "core/allocation/Allocator.h"

class TestAllocator:public Ghurund::Allocator {
private:
    int allocations = 0;

public:
    inline int getAllocations() const {
        return allocations;
    }

    __declspec(property(get = getAllocations)) int Allocations;

    inline void* allocate(Ghurund::memory_t size) {
        allocations++;
        return operator new((size_t)size, _NORMAL_BLOCK, __FILE__, __LINE__);
    }

    inline void deallocate(void* obj) {
        allocations--;
        operator delete(obj);
    }

    inline bool canAllocate(Ghurund::memory_t size) const {
        return true;
    }
};
