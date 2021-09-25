#pragma once

#include "AllocationStrategy.h"
#include "core/collection/List.h"

namespace Ghurund::Core {
    template<typename MemoryType>
    class CircularBufferStrategy:public AllocationStrategy<MemoryType> {
    private:
        MemoryType start = 0, end = 0;
        List<Allocation<MemoryType>> allocations;

    public:
        CircularBufferStrategy() {
            start = 0;
            end = 0;
        }

        inline MemoryType allocate(MemoryType size) {
            MemoryType newStart = align<>(end, __super::alignAddress);
            MemoryType alignedSize = align<>(size, __super::alignSize);
            if (newStart + alignedSize > this->size)
                newStart = end = 0;
            if (__super::allocated > 0 && end <= start && end + alignedSize > start)
                return this->size; // not enough memory in this buffer
            Allocation<MemoryType> a = {alignedSize, newStart};
            allocations.add(a);
            end = newStart + alignedSize;
            __super::allocated += alignedSize;
            return newStart;
        }

        void deallocate(MemoryType address) {
            for (size_t i = 0; i < allocations.Size; i++) {
                const Allocation<MemoryType>& a = allocations[i];
                if (a.address == address) {
                    __super::allocated -= a.size;
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