#include "ghepch.h"
#include "GraphicsFeature.h"

#include "core/reflection/Type.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& GraphicsFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GraphicsFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void GraphicsFeature::uninitGraphicsFeature() {
		resourceManager.Loaders.remove<TextureAtlasLoader>();
		textureAtlasLoader.set(nullptr);
	}

	void GraphicsFeature::onInit() {
		textureAtlasLoader = makeIntrusive<TextureAtlasLoader>(resourceManager);
		resourceManager.Loaders.set<TextureAtlas>(textureAtlasLoader.ref());
	}

	void GraphicsFeature::onUninit() {
		uninitGraphicsFeature();
	}
}
