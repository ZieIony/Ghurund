#include "ghe2dpch.h"
#include "VisualizatonRenderingSystem.h"

#include "VisualizationInputs.h"
#include "VisualizationComponent2D.h"

#include "engine/ecs/World.h"
#include "engine/2d/scene/transform/TransformComponent2D.h"
#include <engine/2d/physics/RigidBodyComponent2D.h>

namespace Ghurund::Engine::_2D {
	void VisualizationRenderingSystem::update(const Timer& timer) {
		auto view = world.entityRegistry.view<VisualizationComponent2D, const RigidBodyComponent2D>();
		for (auto [id, visualization, rigidBody] : view.each()) {
			visualization.update(rigidBody);
		};
    }
    
    void VisualizationRenderingSystem::queueDraw(RenderingContext& renderingContext) {
        RenderGroup group = DrawGroup();
        group.Camera = camera;
        auto view = world.entityRegistry.view<const TransformComponent2D, const VisualizationComponent2D>();
        for (auto [id, transform, visualization] : view.each()) {
            if (!visualization.Mesh || !visualization.Material)
                continue;

            auto w = XMLoadFloat4x4(&visualization.Transformation) * XMLoadFloat4x4(&transform.WorldTransformation);
            XMFLOAT4X4 world;
            XMStoreFloat4x4(&world, XMMatrixTranspose(w));

            // TODO: initialize inputs once
            VisualizationInputs inputs;
            inputs.init(visualization.Material->Inputs);
            inputs.Color = visualization.color;
            inputs.Transformation = world;
            inputs.Extents = { visualization.extents.x * 100, visualization.extents.y * 100 };

            // TODO: maybe not declare draw order manually?
            group.objects.add(DrawPacket(visualization.Mesh, visualization.Material, 0.0f));
        }
        renderingContext.draw(group, parameterManager);
    }
}
