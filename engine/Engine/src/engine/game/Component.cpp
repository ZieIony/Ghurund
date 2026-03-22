#include "ghepch.h"
#include "Component.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& Component::GET_TYPE() {
		static auto PROPERTY_NAME = Property<Component, const AString*>("Name", & getName, (void(Component::*)(const AString*)) & setName);

		static const Ghurund::Core::Type TYPE = TypeBuilder<Component>()
			.withProperty(PROPERTY_NAME)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

#ifdef _DEBUG
	String Component::printTree() const {
		if (Name) {
			return String(std::format(_T("{} '{}'\n"), Type.Name, *Name).c_str());
		} else {
			return String(std::format(_T("{}\n"), Type.Name).c_str());
		}
	}
#endif
}
