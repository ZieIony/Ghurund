#pragma once

#include "TextureProvider.h"

#include "core/resource/ResourceManager.h"
#include "engine/graphics/texture/ITextureFactory.h"

namespace Ghurund::UI {
	using namespace Ghurund::Engine;

	class FileTextureProvider:public TextureProvider {
	private:
		ResourceManager& resourceManager;
		ITextureFactory& textureFactory;
		FilePath resourcePath;
		IntrusivePointer<ITexture> cached;

	public:
		FileTextureProvider(
			ResourceManager& resourceManager,
			ITextureFactory& textureFactory,
			const FilePath& resourcePath
		): resourceManager(resourceManager), textureFactory(textureFactory), resourcePath(resourcePath) {}

		virtual IntrusivePointer<ITexture> get() override {
			if (cached != nullptr)
				return IntrusivePointer<ITexture>((ITexture*)cached->clone());
			auto image = IntrusivePointer<Image>(resourceManager.load<Image>(resourcePath));
			cached = IntrusivePointer<ITexture>(textureFactory.makeTexture(image.ref()));
			return cached;
		}
	};
}