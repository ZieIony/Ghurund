#pragma once

#include "ConstantBuffer.h"
#include "ValueConstant.h"

#include "core/string/String.h"

#include <memory>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class BaseValueParameter;

	class BufferConstant {
	private:
		const AString name;
		uint32_t size;
		Array<ValueConstant> valueConstants;

	public:
		ConstantBuffer* constantBuffer = nullptr;

		BufferConstant(
			const AString& name,
			uint32_t size,
			Array<ValueConstant> valueConstants
		):name(name), size(size), valueConstants(valueConstants) {
		}

		BufferConstant(const BufferConstant& other):name(other.name), size(other.size), valueConstants(other.valueConstants) {}

		BufferConstant(BufferConstant&& other) noexcept:name(other.name), size(other.size), valueConstants(other.valueConstants) {}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline uint32_t getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) uint32_t Size;

		inline const Array<ValueConstant>& getValueConstants() const {
			return valueConstants;
		}

		__declspec(property(get = getValueConstants)) Array<ValueConstant>& ValueConstants;
	};
}