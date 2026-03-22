#include "ghepch.h"
#include "SoundComponent.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& SoundComponent::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SoundComponent>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
