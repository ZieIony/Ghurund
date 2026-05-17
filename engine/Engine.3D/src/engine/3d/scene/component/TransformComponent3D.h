#pragma once

#include "Component3D.h"

#include "core/math/Matrix.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_3D {
	using namespace ::DirectX;

	class TransformComponent3D:public Component3D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TransformComponent3D::GET_TYPE();
#pragma endregion

	private:
		XMFLOAT3 position = {}, rotation = {}, scale = { 1, 1 ,1 };
		XMFLOAT4X4 localTransformation = Ghurund::Core::makeIdentityMatrix();
		XMFLOAT4X4 worldTransformation = Ghurund::Core::makeIdentityMatrix();

	public:
		Event<TransformComponent3D> positionChanged = *this;
		Event<TransformComponent3D> rotationChanged = *this;
		Event<TransformComponent3D> scaleChanged = *this;

		TransformComponent3D(NotNull<Entity3D> owner, World3D& world):Component3D(owner, world) {}

		inline const XMFLOAT4X4& getLocalTransformation() const {
			return localTransformation;
		}

		__declspec(property(get = getLocalTransformation)) const XMFLOAT4X4& LocalTransformation;

		inline const XMFLOAT4X4& getWorldTransformation() const {
			return worldTransformation;
		}

		__declspec(property(get = getWorldTransformation)) const XMFLOAT4X4& WorldTransformation;

		inline XMFLOAT3 getPosition() const {
			return position;
		}

		void setPosition(const XMFLOAT3& pos) {
			if (position.x != pos.x || position.y != pos.y || position.z != pos.z) {
				this->position = pos;
				positionChanged();
			}
		}

		void setPosition(float x, float y, float z) {
			if (position.x != x || position.y != y || position.z != z) {
				this->position.x = x;
				this->position.y = y;
				this->position.z = z;
				positionChanged();
			}
		}

		__declspec(property(get = getPosition, put = setPosition)) const XMFLOAT3& Position;


		inline const XMFLOAT3& getRotation() const {
			return rotation;
		}

		void setRotation(const XMFLOAT3& rotation) {
			if (this->rotation.x != rotation.x || this->rotation.y != rotation.y || this->rotation.z != rotation.z) {
				this->rotation = rotation;
				rotationChanged();
			}
		}

		void setRotation(float yaw, float pitch, float roll) {
			if (this->rotation.x != yaw || this->rotation.y != pitch || this->rotation.z != roll) {
				this->rotation.x = yaw;
				this->rotation.y = pitch;
				this->rotation.z = roll;
				rotationChanged();
			}
		}

		__declspec(property(get = getRotation, put = setRotation)) const XMFLOAT3& Rotation;

		inline const XMFLOAT3& getScale() const {
			return scale;
		}

		void setScale(const XMFLOAT3& scale) {
			if (this->scale.x != scale.x || this->scale.y != scale.y || this->scale.z != scale.z) {
				this->scale = scale;
				scaleChanged();
			}
		}

		void setScale(float x, float y, float z) {
			if (this->scale.x != x || this->scale.y != y || this->scale.z != z) {
				this->scale.x = x;
				this->scale.y = y;
				this->scale.z = z;
				scaleChanged();
			}
		}

		__declspec(property(get = getScale, put = setScale)) const XMFLOAT3& Scale;

		virtual void update(const Timer& timer) override;
	};
}
