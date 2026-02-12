#pragma once

#include "core/Color.h"
#include "engine/graphics/material/MaterialInputCollection.h"
#include "engine/graphics/material/ValueInput.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Engine;
	using namespace ::DirectX;

	class VisualizationInputs {
	private:
		MatrixInput* worldInput = nullptr;
		Float4Input* colorInput = nullptr;
		Float2Input* extentsInput = nullptr;

	public:

		VisualizationInputs() {}

		// this pointer copy is intentional - inputs are managed elsewhere
		VisualizationInputs(
			const VisualizationInputs& other
		):worldInput(other.worldInput), colorInput(other.colorInput) {}

		inline void init(MaterialInputCollection& inputs) {
			worldInput = (MatrixInput*)inputs.get("world");
			colorInput = (Float4Input*)inputs.get("color");
			extentsInput = (Float2Input*)inputs.get("extents");
		}

		inline void setTransformation(const XMFLOAT4X4& world) {
			worldInput->Value = world;
		}

		__declspec(property(put = setTransformation)) const XMFLOAT4X4& Transformation;

		inline void setColor(const Color& color) {
			colorInput->Value = color.toVector();
		}

		__declspec(property(put = setColor)) const Color& Color;

		inline void setExtents(const XMFLOAT2& extents) {
			if (extentsInput)
				extentsInput->Value = extents;
		}

		__declspec(property(put = setExtents)) const XMFLOAT2& Extents;
	};
}
