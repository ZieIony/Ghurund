#pragma once

#include "core/resource/ResourceManager.h"
#include "engine/directx/texture/DxTexture.h"
#include "engine/graphics/texture/TextureProvider.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class DxTextureProvider:public TextureProvider {
	private:
		DxGraphics& graphics;
		CommandList& commandList;

		ITexture* make(const WString& fileName) const {
			return makeFromImage(ResourcePath(ResourceManager::ENGINE_LIB_NAME, fileName));
		}

	public:
		DxTextureProvider(
			DxGraphics& graphics,
			CommandList& commandList,
			ResourceManager& resourceManager,
			ITextureFactory& textureFactory
		):TextureProvider(resourceManager, textureFactory), graphics(graphics), commandList(commandList) {}

		virtual ITexture* makeDefaultDiffuse() const override {
			return make(L"/textures/diffuse.png");
		}

		virtual ITexture* makeDefaultSpecular() const override {
			return make(L"/textures/specular.png");
		}

		virtual ITexture* makeDefaultNormal() const override {
			return make(L"/textures/normal.png");
		}

		virtual ITexture* makeChecker() const override {
			return make(L"/textures/checker.png");
		}
	};
}