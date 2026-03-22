#pragma once

#include "core/string/String.h"
#include "core/object/Initializable.h"
#include "core/object/RefCountedObject.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class Component:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Component::GET_TYPE();
#pragma endregion

	protected:
		Ghurund::Core::AString* name = nullptr;

	public:
		virtual ~Component() = 0 {
			delete name;
		}

		inline const Ghurund::Core::AString* getName() const {
			return name;
		}

		inline void setName(const AString* name) {
			if (this->name)
				delete this->name;
			if (name)
				this->name = ghnew AString(*name);
		}

		inline void setName(const AString& name) {
			if (this->name)
				delete this->name;
			this->name = ghnew AString(name);
		}

		__declspec(property(get = getName, put = setName)) const Ghurund::Core::AString* Name;

#ifdef _DEBUG
		virtual String printTree() const;
#endif
	};
}
