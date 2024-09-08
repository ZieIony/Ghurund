#pragma once

#include "AllocationStrategy.h"
#include "core/collection/List.h"

namespace Ghurund::Core {
    class CircularBufferStrategy:public AllocationStrategy {
    private:
        size_t start = 0, end = 0;
        List<Allocation> allocations;

    public:
        CircularBufferStrategy() {
            start = 0;
            end = 0;
        }

        size_t allocate(size_t size);

        void deallocate(size_t address);
    };

}