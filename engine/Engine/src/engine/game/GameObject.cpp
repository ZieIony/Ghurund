#include "ghepch.h"
#include "GameObject.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& GameObject::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<GameObject>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
