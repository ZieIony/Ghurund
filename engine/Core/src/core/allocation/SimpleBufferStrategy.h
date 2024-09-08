#pragma once

#include "AllocationStrategy.h"
#include "core/collection/List.h"

namespace Ghurund::Core {
    class SimpleBufferStrategy:public AllocationStrategy {
    private:
        List<Allocation> allocations;

    public:
        size_t allocate(size_t size);

        void deallocate(size_t address);
    };
}