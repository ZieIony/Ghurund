#pragma once

#include "Parameter.h"
#include "core/collection/Map.h"
#include "core/string/String.h"
#include "core/IntrusivePointer.h"

namespace Ghurund::Engine {
	class ParameterCollection {
	private:
		Map<AString, IntrusivePointer<Parameter>> parameters;

	public:
		inline void put(Parameter* parameter) {
			parameters.put(parameter->ConstantName, IntrusivePointer(parameter));
		}

		inline Parameter* get(const AString& constantName) const {
			return parameters.get(constantName).get();
		}

		inline Parameter* operator[](const AString& constantName) const {
			return parameters[constantName].get();
		}

		inline void putAll(const ParameterCollection& other) {
			parameters.putAll(other.parameters);
		}
	};
}