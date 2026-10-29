#include "ghepch.h"
#include "System.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& System::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<System>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
