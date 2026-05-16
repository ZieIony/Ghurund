#pragma once

#include "core/feature/Feature.h"
#include "core/reflection/Type.h"
#include "graphics/sprite/SpriteAnimationSetLoader.h"
#include "scene/tiles/TileSetLoader.h"
#include "scene/tiles/TileMapLoader.h"

namespace Ghurund::Engine::_2D {
    using namespace Ghurund::Core;

    class Graphics2DFeature: public Ghurund::Core::Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Graphics2DFeature::GET_TYPE();
#pragma endregion

    private:
        ResourceManager& resourceManager;
        IntrusivePointer<SpriteAnimationSetLoader> animationSetLoader;
        IntrusivePointer<TileSetLoader> tileSetLoader;
        IntrusivePointer<TileMapLoader> tileMapLoader;

        void uninitGraphicsFeature();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        Graphics2DFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        ~Graphics2DFeature() {
            if (IsInitialized)
                uninitGraphicsFeature();
        }
    };
}
