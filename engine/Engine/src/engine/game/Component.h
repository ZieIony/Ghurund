#pragma once

#include "core/string/String.h"
#include "core/object/Initializable.h"
#include "core/object/RefCountedObject.h"
#include "core/object/NamedObject.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class Component:public RefCountedObject, public AStringNamedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Component::GET_TYPE();
#pragma endregion

	public:
		virtual ~Component() = 0 {}

#ifdef _DEBUG
		virtual String printTree() const;
#endif
	};
}
