#pragma once

#include "engine/2d/scene/transform/TransformComponent2D.h"
#include <core/math/Size.h>

#include <box2d.h>
#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	enum class BodyType {
		STATIC = b2_staticBody, KINEMATIC = b2_kinematicBody, DYNAMIC = b2_dynamicBody
	};

	enum class ShapeType {
		BOX, CAPSULE, SEGMENT
	};

	class PhysicsSystem2D;

	class RigidBodyComponent2D {
	private:
		b2BodyId id = {};

		inline b2Polygon makeBox() {
			return b2MakeBox(fabs(scale.x * size.Width) / 2, fabs(scale.y * size.Height) / 2);
		}

		inline b2Capsule makeCapsule() {
			b2Capsule capsule;
			float h = std::max(0.001f, fabs(scale.y * size.Height));
			float r = std::min(h / 2 - 0.001f, fabs(scale.x * size.Width / 2));
			capsule.radius = r;
			capsule.center1 = { 0, -h / 2 + r };
			capsule.center2 = { 0, h / 2 - r };
			return capsule;
		}

		inline b2Segment makeSegment() {
			b2Segment segment;
			float w = fabs(scale.x * size.Width) / 2;
			segment.point1 = { -w, 0 };
			segment.point2 = { w, 0 };
			return segment;
		}

	protected:
		b2ShapeId shapeId = {};
		ShapeType shapeType = ShapeType::BOX;
		XMFLOAT2 scale = { 1, 1 };
		FloatSize size = { 1, 1 };

		bool interpolateTransform = true;

	public:
		void init(PhysicsSystem2D& physicsSystem, Ghurund::Engine::_2D::ShapeType shapeType);

		void deinit() {
			b2DestroyBody(id);
		};

		inline b2BodyId getId() const {
			return id;
		}

		__declspec(property(get = getId)) b2BodyId Id;

		inline void setBodyType(BodyType type) {
			b2Body_SetType(id, (b2BodyType)type);
		}

		inline BodyType getBodyType() const {
			return (Ghurund::Engine::_2D::BodyType)b2Body_GetType(id);
		}

		__declspec(property(get = getBodyType, put = setBodyType)) BodyType BodyType;

		inline ShapeType getShapeType() const {
			return shapeType;
		}

		__declspec(property(get = getShapeType)) ShapeType ShapeType;

		inline XMFLOAT2 getPosition() const {
			b2Vec2 position = b2Body_GetPosition(id);
			return { position.x, position.y };
		}

		inline void setPosition(float x, float y) {
			b2Rot rotation = b2Body_GetRotation(id);
			b2Body_SetTransform(id, { x, y }, rotation);
			b2Body_SetLinearVelocity(id, { 0, 0 });
			b2Body_SetAngularVelocity(id, 0);
		}

		inline void setPosition(const XMFLOAT2& pos) {
			setPosition(pos.x, pos.y);
		}

		__declspec(property(get = getPosition, put = setPosition)) const XMFLOAT2& Position;

		inline float getRotation() const {
			b2Rot rotation = b2Body_GetRotation(id);
			return b2Rot_GetAngle(rotation) / DirectX::XM_PI * 180.0f;
		}

		inline void setRotation(float rotation) {
			b2Vec2 position = b2Body_GetPosition(id);
			float radians = DirectX::XM_PI * rotation / 180.0f;
			b2Body_SetTransform(id, position, { cosf(radians), sinf(radians) });
		}

		__declspec(property(get = getRotation, put = setRotation)) float Rotation;

		inline const FloatSize& getSize() const {
			return size;
		}

		inline void setSize(const FloatSize& size) {
			if (this->size != size) {
				this->size = size;
				updateShape();
			}
		}

		inline void setSize(float width, float height) {
			if (size.Width != width || size.Height != height) {
				size.Width = width;
				size.Height = height;
				updateShape();
			}
		}

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;

		inline bool getInterpolateTransform() const {
			return interpolateTransform;
		}

		inline void setInterpolateTransform(bool interpolateTranform) {
			this->interpolateTransform = interpolateTranform;
		}

		__declspec(property(get = getInterpolateTransform, put = setInterpolateTransform)) bool InterpolateTransform;

		inline void setIsRotationFixed(bool fixed) {
			b2Body_SetFixedRotation(id, fixed);
		}

		inline bool getIsRotationFixed() const {
			return b2Body_IsFixedRotation(id);
		}

		__declspec(property(get = getIsRotationFixed, put = setIsRotationFixed)) bool IsRotationFixed;

		inline XMFLOAT2 getLinearVelocity() const {
			auto vec = b2Body_GetLinearVelocity(id);
			return { vec.x, vec.y };
		}

		__declspec(property(get = getLinearVelocity)) XMFLOAT2 LinearVelocity;

		inline float getAngularVelocity() const {
			return b2Body_GetAngularVelocity(id);
		}

		__declspec(property(get = getAngularVelocity)) float AngularVelocity;

		inline void applyForce(const XMFLOAT2& force) {
			b2Body_ApplyForceToCenter(id, { force.x, force.y }, true);
		}

		void updateShape();

		inline void update(TransformComponent2D& transform) const {
			if (BodyType != BodyType::STATIC) {
				transform.Position = Position;
				transform.Rotation = Rotation;
			}
		}
	};
}
