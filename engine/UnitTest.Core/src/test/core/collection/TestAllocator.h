#pragma once

#include "core/allocation/Allocator.h"

class TestAllocator:public Ghurund::Core::Allocator {
private:
    int allocations = 0;

public:
    inline int getAllocations() const {
        return allocations;
    }

    __declspec(property(get = getAllocations)) int Allocations;

    inline void* allocate(size_t size) {
        allocations++;
        return operator new((size_t)size, _NORMAL_BLOCK, __FILE__, __LINE__);
    }

    inline void deallocate(void* obj) {
        allocations--;
        operator delete(obj);
    }

    inline bool canAllocate(size_t size) const {
        return true;
    }

    inline bool operator==(const TestAllocator& other) const {
        return this == &other;
    }

    inline bool operator!=(const TestAllocator& other) const {
        return this != &other;
    }
};
