#pragma once

#include "core/resource/ResourceManager.h"
#include "engine/directx/texture/Texture.h"
#include "engine/graphics/ITextureProvider.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class TextureProvider:public ITextureProvider {
	private:
		DxGraphics* graphics;
		CommandList* commandList;
		ResourceManager* manager;

		Texture* make(const WString& fileName) const {
			return makeFromImage(ResourcePath(ResourceManager::ENGINE_LIB_NAME, fileName));
		}

	public:
		TextureProvider(
			NotNull<DxGraphics> graphics,
			NotNull<CommandList> commandList,
			NotNull<ResourceManager> manager
		):graphics(&graphics), commandList(&commandList), manager(&manager) {}

		virtual Texture* makeDefaultDiffuse() const override {
			return make(L"/textures/diffuse.png");
		}

		virtual Texture* makeDefaultSpecular() const override {
			return make(L"/textures/specular.png");
		}

		virtual Texture* makeDefaultNormal() const override {
			return make(L"/textures/normal.png");
		}

		virtual Texture* makeChecker() const override {
			return make(L"/textures/checker.png");
		}

		virtual Texture* makeFromImage(const ResourcePath& imagePath) const override {
			Ghurund::Core::Image* image = manager->load<Ghurund::Core::Image>(imagePath, DirectoryPath());
			if (image == nullptr)
				return nullptr;
			Texture* texture = ghnew Texture();
			texture->init(graphics, commandList, *image);
			image->release();
			return texture;
		}
	};
}