#include "ghe2dpch.h"
#include "VisualizatonRenderingSystem.h"

#include "VisualizationComponent2D.h"
#include "VisualizationInputs.h"

#include "engine/2d/graphics/camera/CameraSystem2D.h"
#include "engine/2d/graphics/transform/TransformComponent2D.h"
#include "engine/2d/graphics/transform/TransformSystem2D.h"
#include "engine/2d/physics/RigidBodyComponent2D.h"
#include "engine/2d/World2d.h"

namespace Ghurund::Engine::_2D {
    const Ghurund::Core::Type& VisualizationRenderingSystem::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<VisualizationRenderingSystem>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<std::reference_wrapper<const Ghurund::Core::Type>>& VisualizationRenderingSystem::getDependencies_internal() const {
        static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependencies = { TransformSystem2D::TYPE, CameraSystem2D::TYPE, PhysicsSystem2D::TYPE };
        return dependencies;
    }

    void VisualizationRenderingSystem::update(const Timer& timer) {
		auto view = world.Scene->entityRegistry.view<VisualizationComponent2D, const RigidBodyComponent2D>();
		for (auto [id, visualization, rigidBody] : view.each()) {
			visualization.update(rigidBody);
		};
    }
    
    void VisualizationRenderingSystem::queueDraw(RenderingContext& renderingContext) {
        RenderGroup group = DrawGroup();
        group.Camera = camera;
    
        auto view = world.Scene->entityRegistry.view<const TransformComponent2D, const VisualizationComponent2D>();
        for (auto [id, transform, visualization] : view.each()) {
            if (!visualization.Mesh || !visualization.Material)
                continue;

            ObjectParameters objParameters;
            auto w = XMLoadFloat4x4(&visualization.worldTransformation) * XMLoadFloat4x4(&transform.WorldTransformation);
            XMStoreFloat4x4(&objParameters.world, XMMatrixTranspose(w));

            // TODO: initialize inputs once
            VisualizationInputs inputs;
            inputs.init(visualization.Material->getShader(MaterialVariantType::UNLIT)->Inputs);
            inputs.Color = visualization.color;
            inputs.Extents = { visualization.extents.x * 100, visualization.extents.y * 100 };

            bool culled = false;

            if (!culled) {
                BatchId batchId = { visualization.Mesh->id, visualization.Material->id };
                if (!group.objects.contains(batchId))
                    group.objects.put(batchId, { visualization.Mesh, visualization.Material });
                renderingContext.setParameters(visualization.Id, objParameters);
                group.objects.get(batchId).instances.add(visualization.Id);
            }
        }

		if (!group.objects.IsEmpty)
			renderingContext.draw(group, MaterialVariantType::UNLIT);
    }
}
