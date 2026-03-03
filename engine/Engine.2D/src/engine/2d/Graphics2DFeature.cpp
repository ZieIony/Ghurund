#include "ghe2dpch.h"
#include "Graphics2DFeature.h"

namespace Ghurund::Engine::_2D {
    const Ghurund::Core::Type& Graphics2DFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Graphics2DFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Graphics2DFeature::uninitGraphicsFeature() {
		resourceManager.Loaders.remove<SpriteAnimationSetLoader>();
		animationSetLoader.set(nullptr);
		resourceManager.Loaders.remove<TileSetLoader>();
		tileSetLoader.set(nullptr);
		resourceManager.Loaders.remove<TileMapLoader>();
		tileMapLoader.set(nullptr);
	}

	void Graphics2DFeature::onInit() {
		animationSetLoader = makeIntrusive<SpriteAnimationSetLoader>(resourceManager);
		resourceManager.Loaders.set<SpriteAnimationSet>(animationSetLoader.ref());
		tileSetLoader = makeIntrusive<TileSetLoader>(resourceManager);
		resourceManager.Loaders.set<TileSet>(tileSetLoader.ref());
		tileMapLoader = makeIntrusive<TileMapLoader>(resourceManager);
		resourceManager.Loaders.set<TileMap>(tileMapLoader.ref());
	}

	void Graphics2DFeature::onUninit() {
		uninitGraphicsFeature();
	}
}
