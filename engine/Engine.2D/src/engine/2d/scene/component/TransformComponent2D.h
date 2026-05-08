#pragma once

#include "Component2D.h"

#include "core/math/Matrix.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class TransformComponent2D:public Component2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TransformComponent2D::GET_TYPE();
#pragma endregion

	private:
		XMFLOAT2 position = {}, scale = { 1, 1 };
		float rotation = {};
		XMFLOAT4X4 localTransformation = Ghurund::Core::makeIdentityMatrix();
		XMFLOAT4X4 worldTransformation = Ghurund::Core::makeIdentityMatrix();

	public:
		Event<TransformComponent2D> positionChanged = *this;
		Event<TransformComponent2D> rotationChanged = *this;
		Event<TransformComponent2D> scaleChanged = *this;

		TransformComponent2D(NotNull<Entity2D> owner, World2D& world):Component2D(owner, world) {}

		inline const XMFLOAT4X4& getLocalTransformation() const {
			return localTransformation;
		}

		__declspec(property(get = getLocalTransformation)) const XMFLOAT4X4& LocalTransformation;

		inline const XMFLOAT4X4& getWorldTransformation() const {
			return worldTransformation;
		}

		__declspec(property(get = getWorldTransformation)) const XMFLOAT4X4& WorldTransformation;

		inline XMFLOAT2 getPosition() const {
			return position;
		}

		inline void setPosition(const XMFLOAT2& pos) {
			if (position.x != pos.x || position.y != pos.y) {
				position.x = pos.x;
				position.y = pos.y;
				positionChanged();
			}
		}

		inline void setPosition(float x, float y) {
			if (position.x != x || position.y != y) {
				position.x = x;
				position.y = y;
				positionChanged();
			}
		}

		__declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

		inline float getRotation() const {
			return rotation;
		}

		inline void setRotation(float rotation) {
			if (this->rotation != rotation) {
				this->rotation = rotation;
				rotationChanged();
			}
		}

		__declspec(property(get = getRotation, put = setRotation)) float Rotation;

		inline XMFLOAT2 getScale() const {
			return scale;
		}

		inline void setScale(const XMFLOAT2& scale) {
			if (this->scale.x != scale.x || this->scale.y != scale.y) {
				this->scale.x = scale.x;
				this->scale.y = scale.y;
				scaleChanged();
			}
		}

		inline void setScale(float x, float y) {
			if (scale.x != x || scale.y != y) {
				scale.x = x;
				scale.y = y;
				scaleChanged();
			}
		}

		__declspec(property(get = getScale, put = setScale)) const XMFLOAT2& Scale;

		virtual void update(const Timer& timer) override;

#ifdef _DEBUG
		String print() const;
#endif
	};
}
