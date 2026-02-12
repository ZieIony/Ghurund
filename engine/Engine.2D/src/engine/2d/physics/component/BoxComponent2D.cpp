#include "ghe2dpch.h"
#include "BoxComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& BoxComponent2D::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<BoxComponent2D>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<BoxComponent2D>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void BoxComponent2D::updateSize() {
		b2Polygon box = b2MakeBox(fabs(scale.x * size.Width) / 2, fabs(scale.y * size.Height) / 2);
		b2Shape_SetPolygon(shapeId, &box);
	}
	
	void BoxComponent2D::init(const World2D& world) {
		__super::init(world);

		b2Polygon box = b2MakeBox(fabs(scale.x * size.Width) / 2, fabs(scale.y * size.Height) / 2);
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreatePolygonShape(Id, &shapeDef, &box);
	}
}
