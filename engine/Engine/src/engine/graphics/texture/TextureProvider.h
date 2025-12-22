#pragma once

#include "ITexture.h"
#include "ITextureFactory.h"

#include "core/object/Noncopyable.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class TextureProvider:public Noncopyable {
	private:
		ResourceManager& resourceManager;
		ITextureFactory& textureFactory;

    public:
		TextureProvider(
			ResourceManager& resourceManager,
			ITextureFactory& textureFactory
		):resourceManager(resourceManager), textureFactory(textureFactory) {}

        virtual ITexture* makeDefaultDiffuse() const = 0;

        virtual ITexture* makeDefaultSpecular() const = 0;

        virtual ITexture* makeDefaultNormal() const = 0;

        virtual ITexture* makeChecker() const = 0;

		ITexture* makeFromImage(const ResourcePath& imagePath) const {
			Ghurund::Core::Image* image = resourceManager.load<Ghurund::Core::Image>(imagePath, DirectoryPath());
			if (image == nullptr)
				return nullptr;
			return textureFactory.makeTexture(*image);
		}
	};
}