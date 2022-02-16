#pragma once

#include "Allocator.h"
#include "Common.h"

namespace Ghurund::Core {
    class AllocationStrategy {
    protected:
        size_t size, allocated = 0;
        size_t alignAddress = 1, alignSize = 1;

    public:
        virtual ~AllocationStrategy() {}

        inline void init(size_t size, size_t alignAddress = 1, size_t alignSize = 1) {
            this->size = std::max(size, alignSize);
            this->alignAddress = alignAddress;
            this->alignSize = alignSize;
        }

        virtual size_t allocate(size_t size) = 0;
        virtual void deallocate(size_t) = 0;

		inline size_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

		inline size_t getAllocated() const {
			return allocated;
		}

        __declspec(property(get = getAllocated)) size_t Allocated;

		inline bool canAllocate(size_t size) const {
			return align<>(allocated, alignAddress) + align<>(size, alignSize) <= Size;
		}
    };
}