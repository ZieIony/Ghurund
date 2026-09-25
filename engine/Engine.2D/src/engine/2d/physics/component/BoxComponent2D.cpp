#include "ghe2dpch.h"
#include "BoxComponent2D.h"

#include "engine/2d/scene/component/TransformComponent2D.h"
#include "engine/2d/scene/Entity2D.h"
#include "engine/2d/World2D.h"
#include "engine/2d/Graphics2DFeature.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& BoxComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<BoxComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void BoxComponent2D::uninitBoxComponent2D() {
		if (visualizationComponent) {
			Owner.Components.remove(visualizationComponent);
			visualizationComponent->release();
			visualizationComponent = nullptr;
		}
	}

	CoroutineTask<void> BoxComponent2D::onInit() {
		if (isVisualized) {
			if (visualizationComponent) {
				Owner.Components.remove(visualizationComponent);
				visualizationComponent->release();
			}
			visualizationComponent = Owner.makeComponent<VisualizationComponent2D>();
			visualizationComponent->Mesh = Owner.World.app.ResourceManager.get<Ghurund::Engine::Mesh>(Graphics2DFeature::MESH_SPRITE).get();;
			visualizationComponent->Material = Owner.World.app.ResourceManager.get<Ghurund::Engine::Material>(Graphics2DFeature::MATERIAL_BOX_VISUALIZATION).get();
			Owner.Components.add(visualizationComponent);
		}
		co_await __super::onInit();
	
		b2Polygon box = makeBox();
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreatePolygonShape(Id, &shapeDef, &box);
	}

	void BoxComponent2D::update(const Timer& timer) {
		if (visualizationComponent) {
			XMFLOAT4X4 world;
			auto w = XMMatrixScaling(size.Width, size.Height, 1);
			if (BodyType == BodyType::STATIC) {
				auto rotation = XMMatrixRotationZ(Rotation / 180 * XM_PI);
				auto translation = XMMatrixTranslation(Position.x, Position.y, 0);
				w = w * rotation * translation;
			}
			w = w * XMLoadFloat4x4(&Owner.Transform.WorldTransformation);
			XMStoreFloat4x4(&world, w);
			visualizationComponent->Transformation = world;
			visualizationComponent->Extents = { size.Width / 2, size.Height / 2 };
		}
	}
}
