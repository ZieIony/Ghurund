#pragma once

#include "Component.h"
#include "collection/List.h"

namespace Ghurund {
	template<class Type>
	class System {
	private:
		PointerList<Type*> components;

	public:
		PointerList<Type*>& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) PointerList<Type*>& Components;

		template<class... T>
		void update(float dt, T... params);

		template<class... T>
		Type* makeComponent(T... params);
	};
}