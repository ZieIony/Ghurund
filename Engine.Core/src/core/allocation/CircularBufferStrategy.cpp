#include "CircularBufferStrategy.h"

#include "core/logging/Logger.h"

namespace Ghurund {
    void CircularBufferStrategy::deallocate(memory_t address) {	// TODO: use void*
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
}
