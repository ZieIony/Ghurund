#include "ghcpch.h"
#include "ApplicationWindow.h"

#include "core/reflection/Property.h"

namespace Ghurund::Core {
	const Ghurund::Core::Type& ApplicationWindow::GET_TYPE() {
		static auto PROPERTY_APPLICATION = Property<ApplicationWindow, Ghurund::Core::Application&>("Application", &getApplication);

		static const Ghurund::Core::Type TYPE = TypeBuilder<ApplicationWindow>()
			.withProperty(PROPERTY_APPLICATION)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}