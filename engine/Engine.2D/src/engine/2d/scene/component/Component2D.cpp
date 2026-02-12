#include "ghe2dpch.h"
#include "Component2D.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& Component2D::GET_TYPE() {
		static auto PROPERTY_NAME = Property<Component2D, const AString*>("Name", & getName, (void(Component2D::*)(const AString*)) & setName);

		static const Ghurund::Core::Type TYPE = TypeBuilder<Component2D>()
			.withProperty(PROPERTY_NAME)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

#ifdef _DEBUG
	String Component2D::printTree() const {
		if (Name) {
			return String(std::format(_T("{} '{}'\n"), Type.Name, *Name).c_str());
		} else {
			return String(std::format(_T("{}\n"), Type.Name).c_str());
		}
	}
#endif
}