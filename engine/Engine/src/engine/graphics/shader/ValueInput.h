#pragma once

#include "InputType.h"

#include "core/string/String.h"

#include <memory>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class BaseValueParameter;

	class ValueInput {
	private:
		const AString name;
		const InputType type;
		size_t size, offset;
		const void* defaultValue;

	public:
		void* value = nullptr;

		ValueInput(
			const AString& name,
			InputType type,
			size_t size,
			size_t offset,
			const void* defaultValue
		):name(name), type(type), size(size), offset(offset), defaultValue([&]->const void* {
			if (defaultValue != nullptr) {
				void* copy = ghnew int8_t[size];
				memcpy(copy, defaultValue, size);
				return copy;
			} else {
				return nullptr;
			}
		}()) {
		}

		ValueInput(const ValueInput& other):
			name(other.name),
			type(other.type),
			size(other.size),
			offset(other.offset),
			defaultValue([&]->const void* {
			if (other.defaultValue != nullptr) {
				void* copy = ghnew int8_t[size];
				memcpy(copy, other.defaultValue, size);
				return copy;
			} else {
				return nullptr;
			}
		}()) {
		}

		ValueInput(ValueInput&& other):
			name(other.name),
			type(other.type),
			size(other.size),
			offset(other.offset),
			defaultValue(other.defaultValue) {
			other.defaultValue = nullptr;
		}

		~ValueInput() {
			delete defaultValue;
		}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline InputType getType() const {
			return type;
		}

		__declspec(property(get = getType)) InputType Type;

		template<typename T>
		BaseValueParameter* makeParameter() const {
			T* p = ghnew T(name);
			if (defaultValue)
				p->Value = *(typename T::value_t*)defaultValue;
			return p;
		}

		BaseValueParameter* makeParameter() const;
	};
}