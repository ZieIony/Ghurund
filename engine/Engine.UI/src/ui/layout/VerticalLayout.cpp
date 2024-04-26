#include "ghuipch.h"
#include "VerticalLayout.h"

#include <ui/constraint/PreviousConstraint.h>

namespace Ghurund::UI {
	const Ghurund::Core::Type& VerticalLayout::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<VerticalLayout>();
		static auto PROPERTY_SPACING = Property<VerticalLayout, float>("Spacing", &getSpacing, &setSpacing);
		static Ghurund::Core::Type TYPE = TypeBuilder<VerticalLayout>()
			.withConstructor(CONSTRUCTOR)
			.withProperty(PROPERTY_SPACING)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}