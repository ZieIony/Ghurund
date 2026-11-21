#include "ghe2dpch.h"
#include "SpriteRenderingSystem.h"

#include "engine/2d/graphics/camera/CameraSystem2D.h"
#include "engine/2d/graphics/sprite/SpriteComponent.h"
#include "engine/2d/graphics/transform/TransformComponent2D.h"
#include "engine/2d/graphics/transform/TransformSystem2D.h"
#include "engine/ecs/World.h"
#include "engine/graphics/memory/IGPUMemoryManager.h"
#include "engine/graphics/rendering/ObjectParameters.h"

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

        auto view = world.Scene->entityRegistry.view<TransformComponent2D, SpriteComponent>().each();
        for (auto [id, transform, sprite] : view) {
            if (!sprite.Mesh || !sprite.Material)
                continue;

            ObjectParameters objParameters;
            sprite.update(transform, objParameters);

			sprite.cull(camera->ViewBox);

            if (!sprite.IsCulled) {
                BatchId batchId = { sprite.Mesh->id, sprite.Material->id };
                if (!group.objects.contains(batchId))
                    group.objects.put(batchId, { sprite.Mesh, sprite.Material });
                renderingContext.setParameters(sprite.Id, objParameters);
                group.objects.get(batchId).instances.add(sprite.Id);
            }
        }

		if (!group.objects.IsEmpty)
			renderingContext.draw(group, MaterialVariantType::UNLIT);
	}
}
