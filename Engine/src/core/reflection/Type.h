#pragma once

#include "Constructor.h"

#include <functional>

namespace Ghurund {
	class Object;

	class Type {
	private:
		const BaseConstructor* constructor;
		const char* _namespace;
		const char* name;

		static List<Type>& getTypes() {
			static List<Type> types;
			return types;
		}

	public:
		Type(const char* _namespace, const char* name) {
			this->_namespace = _namespace;
			this->name = name;

			getTypes().add(*this);
		}

		Type(const BaseConstructor& constructor, const char* _namespace, const char* name) {
			this->constructor = &constructor;
			this->_namespace = _namespace;
			this->name = name;

			getTypes().add(*this);
		}

		const BaseConstructor* getConstructor() const {
			return constructor;
		}

		__declspec(property(get = getConstructor)) BaseConstructor* Constructor;

		const char* getNamespace() const {
			return _namespace;
		}

		__declspec(property(get = getNamespace)) const char* Namespace;

		const char* getName() const {
			return name;
		}

		__declspec(property(get = getName)) const char* Name;

		bool operator==(const Type& type) const {
			return constructor == type.constructor && strcmp(_namespace, type._namespace) == 0 && strcmp(name, type.name) == 0;
		}

		inline static const List<Type>& TYPES = getTypes();
	};
}