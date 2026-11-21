#include "ghe3dpch.h"
#include "MeshRenderingSystem.h"

#include "MeshComponent.h"

#include "engine/3d/World3D.h"
#include "engine/3d/graphics/transform/TransformComponent3D.h"
#include "engine/3d/graphics/transform/TransformSystem3D.h"
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

        auto view = world.Scene->entityRegistry.view<TransformComponent3D, MeshComponent>().each();
        for (auto [id, transform, mesh] : view) {
            if (!mesh.Mesh || !mesh.Material)
                continue;

            auto w = XMLoadFloat4x4(&transform.WorldTransformation);
            ObjectParameters objParameters;
            XMStoreFloat4x4(&objParameters.world, XMMatrixTranspose(w));
            
            bool culled = false;// mesh.cullingEnabled&& camera->ViewBox->Contains(transformedBoundingBox) == ContainmentType::DISJOINT;

            //mesh.cull(camera->ViewBox);

            if (!culled) {
                BatchId batchId = { mesh.Mesh->id, mesh.Material->id };
                if (!group.objects.contains(batchId))
                    group.objects.put(batchId, { mesh.Mesh, mesh.Material });
                renderingContext.setParameters(mesh.Id, objParameters);
                group.objects.get(batchId).instances.add(mesh.Id);
            }
        }

        if (!group.objects.IsEmpty)
            renderingContext.draw(group, defaultMaterialType);
    }
}
