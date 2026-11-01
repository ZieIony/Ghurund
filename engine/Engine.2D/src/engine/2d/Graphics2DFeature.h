#pragma once

#include "core/feature/Feature.h"
#include "core/reflection/Type.h"
#include "scene/tiles/TileSetLoader.h"
#include "scene/tiles/TileMapLoader.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/material/Material.h"
#include "graphics/sprite/animation/SpriteAnimationSetLoader.h"

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

        virtual void onDeinit() override;

    public:
        inline static Mesh* MESH_SPRITE = nullptr;

        inline static Material* MATERIAL_SPRITE = nullptr;
        inline static Material* MATERIAL_VISUALIZATION_BOX = nullptr;
        inline static Material* MATERIAL_VISUALIZATION_CAPSULE = nullptr;
        inline static Material* MATERIAL_VISUALIZATION_SEGMENT = nullptr;

        Graphics2DFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual ~Graphics2DFeature() = 0 {
            if (IsInitialized)
                uninitGraphicsFeature();
        }
    };
}
