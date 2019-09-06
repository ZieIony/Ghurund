#pragma once

#include "AllocationStrategy.h"

namespace Ghurund {
    class SimpleBufferStrategy:public AllocationStrategy {
    private:
        List<Allocation> allocations;

    public:
        inline memory_t allocate(memory_t size) {
            if (size > this->size - allocated)
                return this->size;

            memory_t address = 0;
            memory_t alignedSize = align<>(size, alignSize);
            if (allocations.Size == 0) {
                Allocation a = {alignedSize, address};
                allocations.add(a);
                allocated += alignedSize;
                return address;
            } else {
                for (size_t i = 0; i < allocations.Size; i++) {
                    memory_t currAddr = allocations[i].address;
                    if (currAddr >= address + alignedSize) {
                        Allocation a = {alignedSize, address};
                        allocations.insertKeepOrder(i, a);
                        allocated += alignedSize;
                        return address;
                    }
                    address = align<>(currAddr + allocations[i].size, alignAddress);
                }
            }
            if (address + alignedSize <= this->size) {
                Allocation a = {alignedSize, address};
                allocations.add(a);
                allocated += alignedSize;
                return address;
            }
            return this->size;
        }

        inline void deallocate(memory_t address) {
            for (size_t i = 0; i < allocations.Size; i++) {
                Allocation const& a = allocations[i];
                if (a.address == address) {
                    allocated -= a.size;
                    allocations.removeAtKeepOrder(i);
                    return;
                }
            }
            Logger::log(LogType::WARNING, _T("the requested address (%i) does not belong to this strategy\n"), address);
        }
    };
}