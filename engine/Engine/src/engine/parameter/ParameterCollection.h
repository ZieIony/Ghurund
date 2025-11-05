#pragma once

#include "Parameter.h"
#include "core/collection/Map.h"
#include "core/string/String.h"
#include "core/object/IntrusivePointer.h"

namespace Ghurund::Engine {
	class ParameterCollection {
	private:
		Map<AString, IntrusivePointer<Parameter>> parameters;

		ParameterCollection& operator=(const ParameterCollection& other) = delete;

	public:
		inline void put(Parameter* parameter) {
			parameter->addReference();
			parameters.put(parameter->Name, IntrusivePointer(parameter));
		}

		inline Parameter* get(const AString& constantName) const {
			auto it = parameters.find(constantName);
			if (it != parameters.end())
				return it->value.get();
			return nullptr;
		}

		inline Parameter* operator[](const AString& constantName) const {
			return get(constantName);
		}

		inline Map<AString, IntrusivePointer<Parameter>>::iterator begin() {
			return parameters.begin();
		}

		inline Map<AString, IntrusivePointer<Parameter>>::iterator end() {
			return parameters.end();
		}

		inline void putAll(const ParameterCollection& other) {
			parameters.putAll(other.parameters);
		}

		inline void initDefaults(ParameterCollection& other) {
			for (auto& entry : parameters)
				entry.value->initDefault(other);
		}
	};
}