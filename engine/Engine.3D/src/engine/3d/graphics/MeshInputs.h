#pragma once

#include "engine/graphics/material/Material.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_3D {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;
	using namespace ::DirectX;

	class MeshInputs {
	private:
		MatrixInput* worldInput = nullptr;

	public:
		MeshInputs() {}

		// this pointer copy is intentional - inputs are managed elsewhere
		MeshInputs(const MeshInputs& other):worldInput(other.worldInput) {}

		inline void init(MaterialInputCollection& inputs) {
			worldInput = (MatrixInput*)inputs.get(MatrixInput::INPUT_NAME_WORLD);
		}

		inline void setTransformation(const XMFLOAT4X4& world) {
			worldInput->Value = world;
		}

		__declspec(property(put = setTransformation)) const XMFLOAT4X4& Transformation;
	};
}
