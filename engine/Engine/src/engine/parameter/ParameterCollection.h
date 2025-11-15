#pragma once

#include "Parameter.h"
#include "core/collection/Map.h"
#include "core/string/String.h"
#include "core/object/IntrusivePointer.h"

namespace Ghurund::Engine {
	class ParameterCollection {
	private:
		List<IntrusivePointer<Parameter>> parameters;

		ParameterCollection& operator=(const ParameterCollection& other) = delete;

	public:
		inline void put(Parameter* parameter) {
			parameter->addReference();
			parameters.add(IntrusivePointer(parameter));
		}

		inline Parameter* get(const AString& constantName) const {
			auto it = parameters.find([&](auto& item) {return item->Name == constantName; });
			if (it != parameters.Size)
				return parameters[it].get();
			return nullptr;
		}

		inline Parameter* operator[](const AString& constantName) const {
			return get(constantName);
		}

		inline List<IntrusivePointer<Parameter>>::iterator begin() {
			return parameters.begin();
		}

		inline List<IntrusivePointer<Parameter>>::iterator end() {
			return parameters.end();
		}

		inline void putAll(const ParameterCollection& other) {
			parameters.addAll(other.parameters);
		}
	};
}