#pragma once

#include "core/resource/ResourceManager.h"
#include "engine/directx/texture/DxTexture.h"
#include "engine/graphics/texture/ITextureProvider.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class TextureProvider:public ITextureProvider {
	private:
		DxGraphics& graphics;
		CommandList& commandList;
		ResourceManager& manager;

		DxTexture* make(const WString& fileName) const {
			return makeFromImage(ResourcePath(ResourceManager::ENGINE_LIB_NAME, fileName));
		}

	public:
		TextureProvider(
			DxGraphics& graphics,
			CommandList& commandList,
			ResourceManager& manager
		):graphics(graphics), commandList(commandList), manager(manager) {}

		virtual DxTexture* makeDefaultDiffuse() const override {
			return make(L"/textures/diffuse.png");
		}

		virtual DxTexture* makeDefaultSpecular() const override {
			return make(L"/textures/specular.png");
		}

		virtual DxTexture* makeDefaultNormal() const override {
			return make(L"/textures/normal.png");
		}

		virtual DxTexture* makeChecker() const override {
			return make(L"/textures/checker.png");
		}

		virtual DxTexture* makeFromImage(const ResourcePath& imagePath) const override {
			Ghurund::Core::Image* image = manager.load<Ghurund::Core::Image>(imagePath, DirectoryPath());
			if (image == nullptr)
				return nullptr;
			DxTexture* texture = ghnew DxTexture();
			texture->init(graphics, commandList, *image);
			image->release();
			return texture;
		}
	};
}