#include "ghepch.h"
#include "Animation.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& Animation::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Animation>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
