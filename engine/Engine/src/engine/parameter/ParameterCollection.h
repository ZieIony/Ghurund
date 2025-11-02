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
			parameters.put(parameter->ConstantName, IntrusivePointer(parameter));
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

		inline void putAll(const ParameterCollection& other) {
			parameters.putAll(other.parameters);
		}
	};
}