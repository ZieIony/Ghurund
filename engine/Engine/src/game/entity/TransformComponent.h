#pragma once

#include <DirectXMath.h>

namespace Ghurund {
	using namespace ::DirectX;

	class TransformComponent {
	private:
		XMFLOAT3 position = {};
		XMFLOAT3 rotation = {}, scale = { 1,1,1 };
		XMFLOAT4X4 world;

	public:
		inline void update() {
			XMMATRIX local = XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixRotationRollPitchYaw(rotation.y, rotation.x, rotation.z) * XMMatrixTranslation(position.x, position.y, position.z);
			XMStoreFloat4x4(&world, local);
		}

		inline void update(XMFLOAT4X4& parent) {
			XMMATRIX local = XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixRotationRollPitchYaw(rotation.y, rotation.x, rotation.z) * XMMatrixTranslation(position.x, position.y, position.z);
			XMStoreFloat4x4(&world, XMLoadFloat4x4(&parent) * local);
		}

		inline const XMFLOAT4X4& getTransformation() const {
			return world;
		}

		__declspec(property(get = getTransformation)) XMFLOAT4X4& Transformation;

		void setPosition(const XMFLOAT3& pos) {
			this->position = pos;
		}

		void setPosition(float x, float y, float z) {
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
		}

		inline const XMFLOAT3& getPosition() const {
			return position;
		}

		__declspec(property(get = getPosition, put = setPosition)) XMFLOAT3& Position;


		void setRotation(const XMFLOAT3& rotation) {
			this->rotation = rotation;
		}

		void setRotation(float yaw, float pitch, float roll) {
			this->rotation.x = yaw;
			this->rotation.y = pitch;
			this->rotation.z = roll;
		}

		inline const XMFLOAT3& getRotation() const {
			return rotation;
		}

		__declspec(property(get = getRotation, put = setRotation)) XMFLOAT3& Rotation;

		void setScale(const XMFLOAT3& scale) {
			this->scale = scale;
		}

		void setScale(float x, float y, float z) {
			this->scale.x = x;
			this->scale.y = y;
			this->scale.z = z;
		}

		inline const XMFLOAT3& getScale() const {
			return scale;
		}

		__declspec(property(get = getScale, put = setScale)) XMFLOAT3& Scale;
	};
}