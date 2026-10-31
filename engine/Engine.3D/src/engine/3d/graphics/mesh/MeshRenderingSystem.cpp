#include "ghe3dpch.h"
#include "MeshRenderingSystem.h"

#include "MeshComponent.h"
#include "MeshInputs.h"

#include "engine/ecs/World.h"
#include "engine/3d/scene/transform/TransformComponent3D.h"
#include "engine/3d/scene/transform/TransformSystem3D.h"
#include "engine/3d/graphics/camera/CameraSystem3D.h"

namespace Ghurund::Engine::_3D {
    const Ghurund::Core::Type& MeshRenderingSystem::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<MeshRenderingSystem>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<std::reference_wrapper<const Ghurund::Core::Type>>& MeshRenderingSystem::getDependencies_internal() const {
        static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependencies = { TransformSystem3D::TYPE, CameraSystem3D::TYPE };
        return dependencies;
    }

    void MeshRenderingSystem::queueDraw(RenderingContext& renderingContext) {
        RenderGroup group = DrawGroup();
        group.Camera = camera;
        auto view = world.entityRegistry.view<TransformComponent3D, MeshComponent>().each();
        for (auto [id, transform, mesh] : view) {
            if (!mesh.Mesh || !mesh.Material)
                continue;

            auto w = XMLoadFloat4x4(&transform.WorldTransformation);
            XMFLOAT4X4 world;
            XMStoreFloat4x4(&world, XMMatrixTranspose(w));

            MeshInputs inputs;
            inputs.init(mesh.Material->Inputs);
            inputs.Transformation = world;

            // TODO: maybe not declare draw order manually?
            group.objects.add(DrawPacket(mesh.Mesh, mesh.Material, 0.0f));
        }
        renderingContext.draw(group, parameterManager);
    }
}
