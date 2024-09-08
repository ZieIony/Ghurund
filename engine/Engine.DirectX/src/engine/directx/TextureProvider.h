#pragma once

#include "engine/directx/texture/Texture.h"
#include "core/resource/ResourceManager.h"
#include "graphics/ITextureProvider.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class TextureProvider:public ITextureProvider {
	private:
		Graphics& graphics;
		CommandList& commandList;
		ResourceManager& manager;

		Texture* make(const WString& fileName) const {
			return makeFromImage(ResourcePath(ResourceManager::ENGINE_LIB_NAME, fileName));
		}

	public:
		TextureProvider(Graphics& graphics, CommandList& commandList, ResourceManager& manager):graphics(graphics), commandList(commandList), manager(manager) {}

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
			Ghurund::Core::Image* image = manager.load<Ghurund::Core::Image>(imagePath, DirectoryPath());
			if (image == nullptr)
				return nullptr;
			Texture* texture = ghnew Texture();
			texture->init(graphics, commandList, *image);
			image->release();
			return texture;
		}
	};
}