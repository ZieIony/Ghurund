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
        IntrusivePointer<SpriteAnimationSetLoader> animationSetLoader;
        IntrusivePointer<TileSetLoader> tileSetLoader;
        IntrusivePointer<TileMapLoader> tileMapLoader;

        void uninitGraphicsFeature();

    protected:
        ResourceManager& resourceManager;

        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onUninit() override;

    public:
        inline static const WString MESH_SPRITE = L"gh sprite mesh";

        inline static const WString MATERIAL_SPRITE = L"gh sprite material";
        inline static const WString MATERIAL_VISUALIZATION_BOX = L"gh box visualization material";
        inline static const WString MATERIAL_VISUALIZATION_CAPSULE = L"gh capsule visualization material";
        inline static const WString MATERIAL_VISUALIZATION_SEGMENT = L"gh segment visualization material";

        Graphics2DFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual ~Graphics2DFeature() = 0 {
            if (IsInitialized)
                uninitGraphicsFeature();
        }
    };
}
