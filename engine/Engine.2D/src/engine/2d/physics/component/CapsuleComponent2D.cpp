#include "ghe2dpch.h"
#include "CapsuleComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& CapsuleComponent2D::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<CapsuleComponent2D>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<CapsuleComponent2D>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void CapsuleComponent2D::updateSize() {
		b2Capsule capsule;
		float r = fabs(scale.x * size.Width) / 2;
		float h = std::max(0.001f, fabs(scale.y * size.Height) - 2 * r);
		capsule.radius = r;
		capsule.center1 = { 0, -h / 2 };
		capsule.center2 = { 0, h / 2 };
		b2Shape_SetCapsule(shapeId, &capsule);
	}
	
	void CapsuleComponent2D::init(const World2D& world) {
		__super::init(world);

		b2Capsule capsule;
		capsule.radius = 1;
		capsule.center1 = { 0, -0.5 };
		capsule.center2 = { 0, 0.5 };
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreateCapsuleShape(Id, &shapeDef, &capsule);
	}
}
