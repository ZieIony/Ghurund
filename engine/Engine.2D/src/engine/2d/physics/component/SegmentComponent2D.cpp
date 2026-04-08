#include "ghe2dpch.h"
#include "SegmentComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& SegmentComponent2D::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<SegmentComponent2D>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<SegmentComponent2D>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	CoroutineTask<void> SegmentComponent2D::onInit() {
		if (isVisualized) {
			if (visualizationComponent) {
				Components.remove(visualizationComponent);
				visualizationComponent->release();
			}
			visualizationComponent = ghnew VisualizationComponent2D();
			visualizationComponent->Mesh = IntrusivePointer<Mesh>(Owner->Context->makeSpriteMesh()).get();
			visualizationComponent->Material = (co_await Owner->Context->makeSegmentVisualizationMaterial()).get();
			Components.add(visualizationComponent);
		}
		co_await __super::onInit();
	
		b2Segment segment;
		segment.point1 = { -0.5, 0 };
		segment.point2 = { 0.5, 0 };
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreateSegmentShape(Id, &shapeDef, &segment);
	}

	void SegmentComponent2D::updateSize() {
		b2Segment segment;
		float w = fabs(scale.x * size.Width) / 2;
		segment.point1 = { -w, 0 };
		segment.point2 = { w, 0 };
		b2Shape_SetSegment(shapeId, &segment);
		scale.y = 0.02f;
		size.Height = 1;
	}
}
