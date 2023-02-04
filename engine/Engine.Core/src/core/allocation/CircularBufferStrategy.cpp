#include "ghcpch.h"
#include "CircularBufferStrategy.h"
#include "core/logging/Logger.h"

namespace Ghurund::Core {
    size_t CircularBufferStrategy::allocate(size_t size) {
        size_t newStart = align<>(end, __super::alignAddress);
        size_t alignedSize = align<>(size, __super::alignSize);
        if (newStart + alignedSize > this->size)
            newStart = end = 0;
        if (__super::allocated > 0 && end <= start && end + alignedSize > start)
            return this->size; // not enough memory in this buffer
        Allocation a = { alignedSize, newStart };
        allocations.add(a);
        end = newStart + alignedSize;
        __super::allocated += alignedSize;
        return newStart;
    }

    void CircularBufferStrategy::deallocate(size_t address) {
        for (size_t i = 0; i < allocations.Size; i++) {
            const Allocation& a = allocations[i];
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
        auto text = std::format(_T("the requested address (%i) does not belong to this strategy\n"), address);
        Logger::log(LogType::WARNING, text.c_str());
    }
}