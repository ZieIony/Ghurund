#pragma once

#include "core/Color.h"
#include "engine/graphics/material/Material.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Engine;
	using namespace ::DirectX;

	class BodyInputs {
	private:
		MatrixInput* worldInput = nullptr;
		Float4Input* colorInput = nullptr;

	public:
		BodyInputs() {}

		// this pointer copy is intentional - inputs are managed elsewhere
		BodyInputs(
			const BodyInputs& other
		):worldInput(other.worldInput), colorInput(other.colorInput) {}

		inline void init(MaterialInputCollection& inputs) {
			worldInput = (MatrixInput*)inputs.get("world");
			colorInput = (Float4Input*)inputs.get("color");
		}

		inline void setTransformation(const XMFLOAT4X4& world) {
			worldInput->Value = world;
		}

		__declspec(property(put = setTransformation)) const XMFLOAT4X4& Transformation;

		inline void setColor(const Color& color) {
			colorInput->Value = color.toVector();
		}

		__declspec(property(put = setColor)) const Color& Color;
	};
}
