#pragma once

#include "engine/graphics/material/Material.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Engine;
	using namespace ::DirectX;

	class SpriteInputs {
	private:
		Float2Input* sizeInput = nullptr;
		Float2Input* positionInput = nullptr;
		TextureInput* colorTextureInput = nullptr;

	public:
		SpriteInputs() {}

		// this pointer copy is intentional - inputs are managed elsewhere
		SpriteInputs(
			const SpriteInputs& other
		):sizeInput(other.sizeInput), positionInput(other.positionInput), colorTextureInput(colorTextureInput) {}

		inline void init(MaterialInputCollection& inputs) {
			sizeInput = (Float2Input*)inputs.get("size");
			positionInput = (Float2Input*)inputs.get("position");
			colorTextureInput = (TextureInput*)inputs.get("colorTexture");
		}

		inline void setSize(const XMFLOAT2& size) {
			sizeInput->Value = size;
		}

		__declspec(property(put = setSize)) const XMFLOAT2& Size;

		inline void setPosition(const XMFLOAT2& pos) {
			positionInput->Value = pos;
		}

		__declspec(property(put = setPosition)) const XMFLOAT2& Position;

		inline void setColorTexture(ITexture* texture) {
			colorTextureInput->Value = texture;
		}

		__declspec(property(put = setColorTexture)) ITexture* ColorTexture;
	};
}
