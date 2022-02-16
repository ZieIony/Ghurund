#pragma once

#include "Allocator.h"
#include "core/TypeSequence.h"
#include "core/collection/Map.h"

namespace Ghurund::Core {
	class AllocatorMap {
	private:
		Map<size_t, Allocator*> allocators;

	public:
		template<typename Type>
		inline void set(const Allocator& allocator) {
			TypeSequence<AllocatorMap, size_t, Type> seq;
			allocators.set(seq.value(), (Allocator*)& allocator);
		}

		template<typename Type>
		inline Allocator* get() {
			TypeSequence<AllocatorMap, size_t, Type> seq;
			size_t index = allocators.indexOfKey(seq.value());
			if (index == allocators.Size)
				return nullptr;
			return allocators.getValue(index);
		}

		template<typename Type>
		inline void remove() {
			TypeSequence<AllocatorMap, size_t, Type> seq;
			allocators.remove(seq.value());
		}

		inline void clear() {
			allocators.clear();
		}
	};
}