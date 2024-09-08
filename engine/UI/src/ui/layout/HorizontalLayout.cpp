#include "ghuipch.h"
#include "HorizontalLayout.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& HorizontalLayout::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<HorizontalLayout>();
		static auto PROPERTY_SPACING = Property<HorizontalLayout, float>("Spacing", &getSpacing, &setSpacing);
		static Ghurund::Core::Type TYPE = TypeBuilder<HorizontalLayout>()
			.withConstructor(CONSTRUCTOR)
			.withProperty(PROPERTY_SPACING)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}