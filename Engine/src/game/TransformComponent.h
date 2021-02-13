#pragma once

#include "ecs/Component.h"
#include "resource/Resource.h"

#include <DirectXMath.h>

namespace Ghurund {
	using namespace DirectX;

	class TransformComponent :public Component {
	private:
		XMFLOAT3 position = {};
		XMFLOAT3 rotation = {}, scale = { 1,1,1 };
		XMFLOAT4X4 world;

		virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);

		virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

	protected:
		static const Ghurund::Type& GET_TYPE() {
			static const auto CONSTRUCTOR = NoArgsConstructor<TransformComponent>();
			static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(TransformComponent))
				.withConstructor(CONSTRUCTOR)
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

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
			//notifyObjectChanged();
		}

		void setPosition(float x, float y, float z) {
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
			//notifyObjectChanged();
		}

		inline const XMFLOAT3& getPosition() const {
			return position;
		}

		__declspec(property(get = getPosition, put = setPosition)) XMFLOAT3& Position;


		void setRotation(const XMFLOAT3& rotation) {
			this->rotation = rotation;
			//notifyObjectChanged();
		}

		void setRotation(float yaw, float pitch, float roll) {
			this->rotation.x = yaw;
			this->rotation.y = pitch;
			this->rotation.z = roll;
			//notifyObjectChanged();
		}

		inline const XMFLOAT3& getRotation() const {
			return rotation;
		}

		__declspec(property(get = getRotation, put = setRotation)) XMFLOAT3& Rotation;

		void setScale(const XMFLOAT3& scale) {
			this->scale = scale;
			//notifyObjectChanged();
		}

		void setScale(float x, float y, float z) {
			this->scale.x = x;
			this->scale.y = y;
			this->scale.z = z;
			//notifyObjectChanged();
		}

		inline const XMFLOAT3& getScale() const {
			return scale;
		}

		__declspec(property(get = getScale, put = setScale)) XMFLOAT3& Scale;

		inline static const Ghurund::Type& TYPE = GET_TYPE();

		virtual const Ghurund::Type& getType() const override {
			return TYPE;
		}
	};
}