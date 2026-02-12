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

	void SegmentComponent2D::updateSize() {
		b2Segment segment;
		float w = fabs(scale.x * size.Width) / 2;
		segment.point1 = { -w, 0 };
		segment.point2 = { w, 0 };
		b2Shape_SetSegment(shapeId, &segment);
		scale.y = 0.02;
		size.Height = 1;
	}

	void SegmentComponent2D::init(const World2D& world) {
		__super::init(world);

		b2Segment segment;
		segment.point1 = { -0.5, 0 };
		segment.point2 = { 0.5, 0 };
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreateSegmentShape(Id, &shapeDef, &segment);
	}
}
