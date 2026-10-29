#include "ghe2dpch.h"
#include "RigidBodyComponent2D.h"

#include "engine/2d/physics/PhysicsSystem2D.h"

namespace Ghurund::Engine::_2D {
	void RigidBodyComponent2D::init(PhysicsSystem2D& physicsSystem, Ghurund::Engine::_2D::ShapeType shapeType) {
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.position = { 0.0f, 0.0f };
		id = b2CreateBody(physicsSystem.Id, &bodyDef);
		this->shapeType = shapeType;
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		if (shapeType == ShapeType::BOX) {
			b2Polygon box = makeBox();
			shapeId = b2CreatePolygonShape(Id, &shapeDef, &box);
		} else if (shapeType == ShapeType::CAPSULE) {
			b2Capsule capsule = makeCapsule();
			shapeId = b2CreateCapsuleShape(Id, &shapeDef, &capsule);
		} else if (shapeType == ShapeType::SEGMENT) {
			b2Segment segment = makeSegment();
			shapeId = b2CreateSegmentShape(Id, &shapeDef, &segment);
		}
	}

	void RigidBodyComponent2D::updateShape() {
		if (shapeType == ShapeType::BOX) {
			b2Polygon box = makeBox();
			b2Shape_SetPolygon(shapeId, &box);
		} else if (shapeType == ShapeType::CAPSULE) {
			b2Capsule capsule = makeCapsule();
			b2Shape_SetCapsule(shapeId, &capsule);
		} else if (shapeType == ShapeType::SEGMENT) {
			b2Segment segment = makeSegment();
			b2Shape_SetSegment(shapeId, &segment);
		}
	}
}
