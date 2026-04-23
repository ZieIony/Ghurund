#pragma once

#include "engine/2d/scene/component/BaseTransformComponent2D.h"
#include "engine/2d/scene/component/VisualizationComponent2D.h"

#include <box2d.h>
#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	enum class BodyType {
		STATIC = b2_staticBody, KINEMATIC = b2_kinematicBody, DYNAMIC = b2_dynamicBody
	};

	class Simulation2D;

	class BodyComponent2D:public BaseTransformComponent2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = BodyComponent2D::GET_TYPE();
#pragma endregion

	private:
		Simulation2D& simulation;
		b2BodyId id;

	protected:
		bool isVisualized = true;
		VisualizationComponent2D* visualizationComponent = nullptr;

		XMFLOAT2 scale = { 1, 1 };
		FloatSize size = { 1, 1 };

		virtual XMFLOAT2 getPositionInternal() const override {
			b2Vec2 position = b2Body_GetPosition(id);
			return { position.x, position.y };
		}

		virtual void setPositionInternal(float x, float y) override {
			b2Rot rotation = b2Body_GetRotation(id);
			b2Body_SetTransform(id, { x, y }, rotation);
			b2Body_SetLinearVelocity(id, { 0, 0 });
			b2Body_SetAngularVelocity(id, 0);
		}

		virtual float getRotationInternal() const override {
			b2Rot rotation = b2Body_GetRotation(id);
			return b2Rot_GetAngle(rotation) / DirectX::XM_PI * 180.0f;
		}

		virtual void setRotationInternal(float rotation) override {
			b2Vec2 position = b2Body_GetPosition(id);
			float radians = DirectX::XM_PI * rotation / 180.0f;
			b2Body_SetTransform(id, position, { cosf(radians), sinf(radians) });
		}

		virtual XMFLOAT2 getScaleInternal() const override {
			return scale;
		}

		virtual void setScaleInternal(float x, float y) override {
			scale.x = x;
			scale.y = y;
			updateSize();
		}

		virtual CoroutineTask<void> onInit() override;

		inline void uninitBodyComponent2D() {
			b2DestroyBody(id);
		};

		virtual void onUninit() {
			uninitBodyComponent2D();
			__super::onUninit();
		};

		virtual void updateSize() = 0;

	public:
		BodyComponent2D(NotNull<Entity2D> owner, World2D& world);

		virtual ~BodyComponent2D() = 0 {
			if (IsInitialized)
				uninitBodyComponent2D();
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

		inline void setSize(const FloatSize& size) {
			this->size = size;
			updateSize();
		}

		inline const FloatSize& getSize() const {
			return size;
		}

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;

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

		virtual void update(const XMFLOAT4X4& parentTransformation, const Timer& timer) override;
	};
}
