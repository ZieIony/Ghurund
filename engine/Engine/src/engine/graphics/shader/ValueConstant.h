#pragma once

#include "InputType.h"

#include "core/string/String.h"

#include <memory>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ValueConstant {
	private:
		const AString name;
		const InputType type;
		const size_t size, offset;
		const void* defaultValue;
		const void* value = nullptr;

	public:
		ValueConstant(
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

		ValueConstant(const ValueConstant& other):
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

		ValueConstant(ValueConstant&& other) noexcept:
			name(other.name),
			type(other.type),
			size(other.size),
			offset(other.offset),
			defaultValue(other.defaultValue) {
			other.defaultValue = nullptr;
		}

		~ValueConstant() {
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

		inline size_t getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) size_t Size;

		inline size_t getOffset() const {
			return offset;
		}

		__declspec(property(get = getOffset)) size_t Offset;

		inline const void* getValue() const {
			return value;
		}

		inline void setValue(const void* value) {
			this->value = value;
		}

		__declspec(property(get = getValue, put = setValue)) const void* Value;

		inline const void* getDefaultValue() const {
			return defaultValue;
		}

		__declspec(property(get = getDefaultValue)) const void* DefaultValue;
	};
}