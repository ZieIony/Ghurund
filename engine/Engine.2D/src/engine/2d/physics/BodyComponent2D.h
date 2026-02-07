#pragma once

#include "BodyInputs.h"
#include "World2D.h"

#include "engine/2d/entity/Component2D.h"

#include <box2d.h>
#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	enum class BodyType {
		STATIC = b2_staticBody, KINEMATIC = b2_kinematicBody, DYNAMIC = b2_dynamicBody
	};

	class BodyComponent2D:public ComponentGroup2D {
	private:
		bool initialized = false;
		b2BodyId id;

		Mesh* mesh = nullptr;
		Material* material = nullptr;
		Color color = Color(random() / 2 + 0.5f, random() / 2 + 0.5f, random() / 2 + 0.5f);
		BodyInputs inputs;

	protected:
		virtual XMFLOAT2 getPositionInternal() const override {
			b2Vec2 position = b2Body_GetPosition(id);
			return { position.x, position.y };
		}

		virtual void setPositionInternal(const XMFLOAT2& pos) override {
			b2Rot rotation = b2Body_GetRotation(id);
			b2Body_SetTransform(id, { pos.x, pos.y }, rotation);
			b2Body_SetLinearVelocity(id, { 0, 0 });
			b2Body_SetAngularVelocity(id, 0);
		}

	public:
		BodyComponent2D() {}

		BodyComponent2D(NotNull<Mesh> mesh, NotNull<Material> material):mesh(mesh.get()), material(material.get()) {
			mesh->addReference();
			material->addReference();
			inputs.init(material->Inputs);
			inputs.Color = color;
		}

		virtual ~BodyComponent2D() = 0 {
			if (mesh)
				mesh->release();
			if (material)
				material->release();
			if (initialized)
				uninit();
		}

		inline void init(const World2D& world) {
			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.position = { 0.0f, 0.0f };
			id = b2CreateBody(world.Id, &bodyDef);
			initialized = true;
		}

		inline void uninit() {
			b2DestroyBody(id);
			initialized = false;
		}

		inline b2BodyId getId() const {
			return id;
		}

		__declspec(property(get = getId)) b2BodyId Id;

		inline void setType(BodyType type) {
			b2Body_SetType(id, (b2BodyType)type);
		}

		inline BodyType getType() const {
			return (BodyType)b2Body_GetType(id);
		}

		__declspec(property(get = getType, put = setType)) BodyType Type;

		inline void setIsRotationFixed(bool fixed) {
			b2Body_SetFixedRotation(id, fixed);
		}

		inline bool getIsRotationFixed() const {
			return b2Body_IsFixedRotation(id);
		}

		__declspec(property(get = getIsRotationFixed, put = setIsRotationFixed)) bool IsRotationFixed;

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

		virtual void setSize(const FloatSize& size) = 0;

		virtual const FloatSize& getSize() const = 0;

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;

		inline void applyForce(const XMFLOAT2& force) {
			b2Body_ApplyForceToCenter(id, { force.x, force.y }, true);
		}

		virtual void draw(RenderGroup& group, const XMFLOAT4X4& parentTransformation) override;
	};
}