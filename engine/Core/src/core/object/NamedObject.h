#pragma once

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"
#include "core/string/String.h"

namespace Ghurund::Core {
	template<class StringType>
	class NamedObject {
	protected:
		StringType* name = nullptr;

	public:
		virtual ~NamedObject() = 0 {
			delete name;
		}

		inline const StringType* getName() const {
			return name;
		}

		inline void setName(const StringType* name) {
			if (this->name)
				delete this->name;
			if (name)
				this->name = ghnew StringType(*name);
		}

		inline void setName(const StringType& name) {
			if (this->name)
				delete this->name;
			this->name = ghnew StringType(name);
		}

		__declspec(property(get = getName, put = setName)) const StringType* Name;

	protected:
		static inline auto PROPERTY_NAME = Property<NamedObject, const StringType*>("Name", &getName, (void(NamedObject::*)(const StringType*))& setName);
	};

	typedef NamedObject<WString> WStringNamedObject;
	typedef NamedObject<AString> AStringNamedObject;

	template<>
	const Type& getType<WStringNamedObject>();

	template<>
	const Type& getType<AStringNamedObject>();
}
