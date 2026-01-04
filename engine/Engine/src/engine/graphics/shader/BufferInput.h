#pragma once

#include "ConstantBuffer.h"
#include "ValueInput.h"

#include "core/string/String.h"

#include <memory>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class BaseValueParameter;

	class BufferInput {
	private:
		const AString name;
		Array<ValueInput> valueInputs;

	public:
		ConstantBuffer* constantBuffer = nullptr;

		BufferInput(
			const AString& name,
			Array<ValueInput> valueInputs
		):name(name), valueInputs(valueInputs) {
		}

		BufferInput(const BufferInput& other):name(other.name), valueInputs(other.valueInputs) {}

		BufferInput(BufferInput&& other) noexcept:name(other.name), valueInputs(other.valueInputs) {}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline const Array<ValueInput>& getValueInputs() const {
			return valueInputs;
		}

		__declspec(property(get = getValueInputs)) Array<ValueInput>& ValueInputs;

		Array<BaseValueParameter*> makeParameters() const {
			Array<BaseValueParameter*> parameters(valueInputs.Size);
			for (size_t i = 0; i < valueInputs.Size; i++) {
				auto& input = valueInputs[i];
				parameters[i] = input.makeParameter();
			}
			return parameters;
		}
	};
}