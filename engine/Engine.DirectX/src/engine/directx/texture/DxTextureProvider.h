#pragma once

#include "core/resource/ResourceManager.h"
#include "engine/directx/texture/DxTexture.h"
#include "engine/graphics/texture/TextureProvider.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class DxTextureProvider:public TextureProvider {
	private:
		ResourceManager& resourceManager;

	public:
		DxTextureProvider(
			ResourceManager& resourceManager
		):resourceManager(resourceManager) { }

		virtual ITexture* makeDefaultDiffuse() const override {
			return resourceManager.load<ITexture>(ResourceManager::ENGINE_LIB / FilePath(L"/textures/diffuse.png"));
		}

		virtual ITexture* makeDefaultSpecular() const override {
			return resourceManager.load<ITexture>(ResourceManager::ENGINE_LIB / FilePath(L"/textures/specular.png"));
		}

		virtual ITexture* makeDefaultNormal() const override {
			return resourceManager.load<ITexture>(ResourceManager::ENGINE_LIB / FilePath(L"/textures/normal.png"));
		}

		virtual ITexture* makeChecker() const override {
			return resourceManager.load<ITexture>(ResourceManager::ENGINE_LIB / FilePath(L"/textures/checker.png"));
		}
	};
}