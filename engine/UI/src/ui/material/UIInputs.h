#pragma once

#include "engine/graphics/material/Material.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
	using namespace Ghurund::Engine;
	using namespace ::DirectX;

	class UIInputs {
	private:
		Float2Input* sizeInput = nullptr;
		Float2Input* positionInput = nullptr;

	public:
		UIInputs() {}

		// this pointer copy is intentional - inputs are managed elsewhere
		UIInputs(const UIInputs& other):sizeInput(other.sizeInput), positionInput(other.positionInput) {}

		inline void init(MaterialInputCollection& inputs) {
			sizeInput = (Float2Input*)inputs.get("size");
			positionInput = (Float2Input*)inputs.get("position");
		}

		inline void setSize(const XMFLOAT2& size) {
			sizeInput->Value = size;
		}

		__declspec(property(put = setSize)) const XMFLOAT2& Size;

		inline void setPosition(const XMFLOAT2& pos) {
			positionInput->Value = pos;
		}

		__declspec(property(put = setPosition)) const XMFLOAT2& Position;
	};
}
