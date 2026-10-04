#include "ghepch.h"
#include "GraphicsFeature.h"

#include "core/reflection/Type.h"
#include "mesh/MeshDataLoader.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& GraphicsFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GraphicsFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void GraphicsFeature::uninitGraphicsFeature() {
		resourceManager.Loaders.remove<TextureAtlas>();
		resourceManager.Loaders.remove<MeshData>();
	}

	CoroutineTask<void> GraphicsFeature::onInit() {
		auto meshDataLoader = makeIntrusive<MeshDataLoader>();
		resourceManager.Loaders.set<MeshData>(meshDataLoader.ref());
		auto textureAtlasLoader = makeIntrusive<TextureAtlasLoader>(resourceManager);
		resourceManager.Loaders.set<TextureAtlas>(textureAtlasLoader.ref());
		co_return;
	}

	void GraphicsFeature::onUninit() {
		uninitGraphicsFeature();
	}
}
