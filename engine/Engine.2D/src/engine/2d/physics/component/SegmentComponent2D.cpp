#include "ghe2dpch.h"
#include "SegmentComponent2D.h"

#include "engine/2d/scene/Entity2D.h"
#include "engine/2d/World2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& SegmentComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SegmentComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void SegmentComponent2D::uninitSegmentComponent2D() {
		Owner->Transform.scaleChanged -= scaleChangedHandler;
		if (visualizationComponent) {
			Owner->Components.remove(visualizationComponent);
			visualizationComponent->release();
			visualizationComponent = nullptr;
		}
	}

	CoroutineTask<void> SegmentComponent2D::onInit() {
		if (isVisualized) {
			if (visualizationComponent) {
				Owner->Components.remove(visualizationComponent);
				visualizationComponent->release();
			}
			visualizationComponent = Owner->makeComponent<VisualizationComponent2D>();
			visualizationComponent->Mesh = IntrusivePointer<Mesh>(Owner->World.context->makeSpriteMesh()).get();
			visualizationComponent->Material = (co_await Owner->World.context->makeSegmentVisualizationMaterial()).get();
			Owner->Components.add(visualizationComponent);
		}
		co_await __super::onInit();
	
		b2Segment segment = makeSegment();
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreateSegmentShape(Id, &shapeDef, &segment);

		Owner->Transform.scaleChanged += scaleChangedHandler;
	}

	void SegmentComponent2D::update(const Timer& timer) {
		if (visualizationComponent) {
			XMFLOAT4X4 world;
			auto w = XMMatrixScaling(width, 0.02f, 1);
			if (BodyType == BodyType::STATIC) {
				auto rotation = XMMatrixRotationZ(Rotation / 180 * XM_PI);
				auto translation = XMMatrixTranslation(Position.x, Position.y, 0);
				w = w * rotation * translation;
			}
			w = w * XMLoadFloat4x4(&Owner->Transform.WorldTransformation);
			XMStoreFloat4x4(&world, w);
			visualizationComponent->Transformation = world;
			visualizationComponent->Extents = { width / 2, 0.02f };
		}
	}
}
