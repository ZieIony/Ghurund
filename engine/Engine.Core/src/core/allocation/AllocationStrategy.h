#pragma once

#include "Allocator.h"
#include "Common.h"

namespace Ghurund::Core {
    template<typename T = size_t>
    class AllocationStrategy {
    protected:
        T size, allocated = 0;
        T alignAddress, alignSize;

    public:
        virtual ~AllocationStrategy() {}

        inline void init(T size, T alignAddress = 1, T alignSize = 1) {
            this->size = std::max(size, alignSize);
            this->alignAddress = alignAddress;
            this->alignSize = alignSize;
        }

        virtual T allocate(T size) = 0;
        virtual void deallocate(T) = 0;

		inline T getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) T Size;

		inline T getAllocated() const {
			return allocated;
		}

        __declspec(property(get = getAllocated)) T Allocated;

		inline bool canAllocate(T size) const {
			return align<>(allocated, alignAddress) + align<>(size, alignSize) <= Size;
		}
    };
}