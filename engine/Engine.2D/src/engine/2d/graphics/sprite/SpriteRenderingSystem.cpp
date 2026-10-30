#include "ghe2dpch.h"
#include "SpriteRenderingSystem.h"
#include "SpriteInputs.h"

#include "engine/ecs/World.h"
#include "engine/2d/scene/transform/TransformComponent2D.h"
#include "engine/2d/graphics/sprite/SpriteComponent.h"
#include "engine/2d/scene/transform/TransformSystem2D.h"
#include "engine/2d/scene/camera/CameraSystem2D.h"

namespace Ghurund::Engine::_2D {
    const Ghurund::Core::Type& SpriteRenderingSystem::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteRenderingSystem>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<std::reference_wrapper<const Ghurund::Core::Type>>& SpriteRenderingSystem::getDependencies_internal() const {
        static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependencies = { TransformSystem2D::TYPE, CameraSystem2D::TYPE };
        return dependencies;
    }

    void SpriteRenderingSystem::queueDraw(RenderingContext& renderingContext) {
        RenderGroup group = DrawGroup();
        group.Camera = camera;
        auto view = world.entityRegistry.view<TransformComponent2D, SpriteComponent>().each();
        for (auto [id, transform, sprite] : view) {
            if (!sprite.Mesh || !sprite.Material)
                continue;

            auto w = XMMatrixTranslation(sprite.offset.x, sprite.offset.y, 0) *
                XMMatrixScaling(sprite.size.Width, sprite.size.Height, 1) *
                XMLoadFloat4x4(&transform.WorldTransformation);
            XMFLOAT4X4 world;
            XMStoreFloat4x4(&world, XMMatrixTranspose(w));

            // TODO: initialize inputs once
            SpriteInputs inputs;
            inputs.init(sprite.Material->Inputs);
            inputs.Transformation = world;
            inputs.Tint = sprite.tint;
            inputs.Alpha = sprite.alpha;
            inputs.ColorTexture = sprite.ColorTexture;

            // TODO: maybe not declare draw order manually?
            group.objects.add(DrawPacket(sprite.Mesh, sprite.Material, 0.0f));
        }
        renderingContext.draw(group, parameterManager);
    }
}
