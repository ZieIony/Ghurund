#pragma once

#include "TextureProvider.h"

#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
	using namespace Ghurund::Engine;

	class FileTextureProvider:public TextureProvider {
	private:
		ResourceManager& resourceManager;
		FilePath resourcePath;
		IntrusivePointer<ITexture> cached;

	public:
		FileTextureProvider(
			ResourceManager& resourceManager,
			const FilePath& resourcePath
		): resourceManager(resourceManager), resourcePath(resourcePath) {}

		virtual IntrusivePointer<ITexture> get() override {
			if (cached != nullptr)
				return IntrusivePointer<ITexture>((ITexture*)cached->clone());
			auto coroutine = resourceManager.load<ITexture>(resourcePath);
			coroutine.resume();
			cached = coroutine.Result;
			return cached;
		}
	};
}