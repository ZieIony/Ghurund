#pragma once

#include "AllocationStrategy.h"

namespace Ghurund {
    class CircularBufferStrategy:public AllocationStrategy {
    private:
        memory_t start = 0, end = 0;
        List<Allocation> allocations;

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

        inline void deallocate(memory_t address) {	// TODO: use void*
            for (size_t i = 0; i < allocations.Size; i++) {
                const Allocation& a = allocations[i];
                if (a.address == address) {
                    allocated -= a.size;
                    allocations.removeAt(i);
                    if (allocations.Size > 0) {
                        start = allocations[0].address;
                    } else {
                        start = end = 0;
                    }
                    return;
                }
            }
            Logger::log(LogType::WARNING, _T("the requested address (%i) does not belong to this strategy\n"), address);
        }
    };

}