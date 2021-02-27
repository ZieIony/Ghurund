#pragma once

#include "Allocator.h"
#include "Common.h"

#include <algorithm>
#undef min
#undef max

namespace Ghurund {
    class AllocationStrategy {
    protected:
        memory_t size, allocated = 0;
        memory_t alignAddress, alignSize;

    public:
        virtual ~AllocationStrategy() {}

        void init(memory_t size, memory_t alignAddress = 1, memory_t alignSize = 1) {
            this->size = std::max(size, alignSize);
            this->alignAddress = alignAddress;
            this->alignSize = alignSize;
        }

        virtual memory_t allocate(memory_t size) = 0;
        virtual void deallocate(memory_t) = 0;

		inline memory_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) memory_t Size;

		inline memory_t getAllocated() const {
			return allocated;
		}

        __declspec(property(get = getAllocated)) memory_t Allocated;

		inline bool canAllocate(memory_t size) const {
			return align<>(allocated, alignAddress) + align<>(size, alignSize) <= Size;
		}
    };
}