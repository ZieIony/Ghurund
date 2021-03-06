#pragma once

#include "Allocator.h"
#include "core/reflection/Type.h"
#include "core/collection/Map.h"

namespace Ghurund {
	class AllocatorMap {
	private:
		Map<Type*, Allocator*> allocators;

	public:
		inline void set(const Type& type, const Allocator& allocator) {
			allocators.set((Type*)& type, (Allocator*)& allocator);
		}

		inline Allocator* get(const Type& type) {
			size_t index = allocators.indexOfKey((Type*)& type);
			if (index == allocators.Size)
				return nullptr;
			return allocators.getValue(index);
		}

		inline void remove(const Type& type) {
			allocators.remove((Type*)& type);
		}

		inline void clear() {
			allocators.clear();
		}
	};
}