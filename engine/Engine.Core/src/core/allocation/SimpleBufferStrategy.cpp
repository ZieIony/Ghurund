#include "ghcpch.h"
#include "SimpleBufferStrategy.h"
#include "core/logging/Logger.h"

namespace Ghurund::Core {
    size_t SimpleBufferStrategy::allocate(size_t size) {
        if (size > this->size - allocated)
            return this->size;

        size_t address = 0;
        size_t alignedSize = align<>(size, alignSize);
        if (allocations.Size == 0) {
            Allocation a = { alignedSize, address };
            allocations.add(a);
            allocated += alignedSize;
            return address;
        } else {
            for (size_t i = 0; i < allocations.Size; i++) {
                size_t currAddr = allocations[i].address;
                if (currAddr >= address + alignedSize) {
                    Allocation a = { alignedSize, address };
                    allocations.insert(i, a);
                    allocated += alignedSize;
                    return address;
                }
                address = align<>(currAddr + allocations[i].size, alignAddress);
            }
        }
        if (address + alignedSize <= this->size) {
            Allocation a = { alignedSize, address };
            allocations.add(a);
            allocated += alignedSize;
            return address;
        }
        return this->size;
    }

    void SimpleBufferStrategy::deallocate(size_t address) {
        for (size_t i = 0; i < allocations.Size; i++) {
            Allocation const& a = allocations[i];
            if (a.address == address) {
                allocated -= a.size;
                allocations.removeAt(i);
                return;
            }
        }
        Logger::log(LogType::WARNING, _T("the requested address (%i) does not belong to this strategy\n"), address);
    }
}