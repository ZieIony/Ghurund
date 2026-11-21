#pragma once

#include "core/Color.h"
#include "engine/graphics/material/Material.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;
	using namespace ::DirectX;

	class SpriteInputs {
	private:
		TextureInput* colorTextureInput = nullptr;
		Float3Input* tintInput = nullptr;
		FloatInput* alphaInput = nullptr;

	public:
		SpriteInputs() {}

		// this pointer copy is intentional - inputs are managed elsewhere
		SpriteInputs(const SpriteInputs& other):
			colorTextureInput(other.colorTextureInput),
			tintInput(other.tintInput),
			alphaInput(other.alphaInput) {
		}

		inline void init(MaterialInputCollection& inputs) {
			colorTextureInput = (TextureInput*)inputs.get("colorTexture");
			tintInput = (Float3Input*)inputs.get("tint");
			alphaInput = (FloatInput*)inputs.get("alpha");
		}

		inline void setTint(const Color& color) {
			tintInput->Value = { color.R, color.G, color.B };
		}

		__declspec(property(put = setTint)) const Color& Tint;

		inline void setAlpha(float alpha) {
			alphaInput->Value = alpha;
		}

		__declspec(property(put = setAlpha)) float Alpha;

		inline void setColorTexture(ITexture* texture) {
			colorTextureInput->Value = texture;
		}

		__declspec(property(put = setColorTexture)) ITexture* ColorTexture;
	};
}
