#pragma once

#include "Allocator.h"
#include "core/TypeSequence.h"
#include "core/collection/Map.h"

namespace Ghurund::Core {
	template<typename MemoryType>
	class AllocatorMap {
	private:
		typename size_t key_t;
		Map<key_t, Allocator<MemoryType>*> allocators;

	public:
		template<typename Type>
		inline void set(const Allocator<MemoryType>& allocator) {
			TypeSequence<AllocatorMap<MemoryType>, key_t, Type> seq;
			allocators.set(seq.value(), (Allocator<MemoryType>*)& allocator);
		}

		template<typename Type>
		inline Allocator<MemoryType>* get() {
			TypeSequence<AllocatorMap<MemoryType>, key_t, Type> seq;
			size_t index = allocators.indexOfKey(seq.value());
			if (index == allocators.Size)
				return nullptr;
			return allocators.getValue(index);
		}

		template<typename Type>
		inline void remove() {
			TypeSequence<AllocatorMap<MemoryType>, key_t, Type> seq;
			allocators.remove(seq.value());
		}

		inline void clear() {
			allocators.clear();
		}
	};
}