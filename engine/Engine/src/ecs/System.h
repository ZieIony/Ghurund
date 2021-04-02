#pragma once

#include "Component.h"
#include "core/collection/PointerList.h"
#include "core/Object.h"
#include "core/allocation/Allocator.h"

namespace Ghurund {
	template<class Type>
	class System {
	private:
		PointerList<Type*> components;
		Allocator* allocator = ghnew SimpleAllocator();

	public:
		~System() {
			delete allocator;
		}

		PointerList<Type*>& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) PointerList<Type*>& Components;

		Type* makeComponent() {
			Type* c = ghnew Type();
			components.add(c);
			return c;
		}

		inline Allocator& getAllocator() const {
			return *allocator;
		}

		__declspec(property(get = getAllocator)) Allocator& Allocator;
	};
}