#pragma once

#include "core/math/Matrix.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_3D {
	using namespace ::DirectX;

	class TransformComponent3D {
	private:
		XMFLOAT3 position = {}, rotation = {}, scale = { 1, 1 ,1 };
		XMFLOAT4X4 localTransformation = Ghurund::Core::makeIdentityMatrix();
		XMFLOAT4X4 worldTransformation = Ghurund::Core::makeIdentityMatrix();

	public:
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
			this->position = pos;
		}

		void setPosition(float x, float y, float z) {
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
		}

		__declspec(property(get = getPosition, put = setPosition)) const XMFLOAT3& Position;


		inline const XMFLOAT3& getRotation() const {
			return rotation;
		}

		void setRotation(const XMFLOAT3& rotation) {
			this->rotation = rotation;
		}

		void setRotation(float yaw, float pitch, float roll) {
			this->rotation.x = yaw;
			this->rotation.y = pitch;
			this->rotation.z = roll;
		}

		__declspec(property(get = getRotation, put = setRotation)) const XMFLOAT3& Rotation;

		inline const XMFLOAT3& getScale() const {
			return scale;
		}

		void setScale(const XMFLOAT3& scale) {
			this->scale = scale;
		}

		void setScale(float x, float y, float z) {
			this->scale.x = x;
			this->scale.y = y;
			this->scale.z = z;
		}

		__declspec(property(get = getScale, put = setScale)) const XMFLOAT3& Scale;

		inline void update() {
			auto scaling = XMMatrixScaling(scale.x, scale.y, scale.z);
			auto rotation = XMMatrixRotationRollPitchYaw(this->rotation.y, this->rotation.x, this->rotation.z);
			auto translation = XMMatrixTranslation(position.x, position.y, position.z);
			auto local = scaling * rotation * translation;
			XMStoreFloat4x4(&localTransformation, local);

			XMStoreFloat4x4(&worldTransformation, local);// * XMLoadFloat4x4(&parentTransformation));
		}
	};
}
