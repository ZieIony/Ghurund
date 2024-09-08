#include "ghuipch.h"
#include "ValueConstraint.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ValueConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ValueConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}