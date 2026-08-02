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
		XMFLOAT2 position = {}, scale = { 1, 1 }, up = { 0, 1 }, right = { 1, 0 };
		float rotation = {};
		XMFLOAT4X4 localTransformation = Ghurund::Core::makeIdentityMatrix();
		XMFLOAT4X4 worldTransformation = Ghurund::Core::makeIdentityMatrix();

	public:
		TransformComponent2D(NotNull<Entity2D> owner):Component2D(owner) {}

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
			position.x = pos.x;
			position.y = pos.y;
		}

		inline void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		__declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

		inline float getRotation() const {
			return rotation;
		}

		inline void setRotation(float rotation) {
			this->rotation = rotation;
		}

		__declspec(property(get = getRotation, put = setRotation)) float Rotation;

		inline XMFLOAT2 getScale() const {
			return scale;
		}

		inline void setScale(const XMFLOAT2& scale) {
			this->scale.x = scale.x;
			this->scale.y = scale.y;
		}

		inline void setScale(float x, float y) {
			scale.x = x;
			scale.y = y;
		}

		__declspec(property(get = getScale, put = setScale)) const XMFLOAT2& Scale;

		inline const XMFLOAT2& getUp() const {
			return up;
		}

		inline void setUp(const XMFLOAT2& up) {
			if (this->up.x != up.x || this->up.y != up.y) {
				auto v = DirectX::XMLoadFloat2(&up);
				auto n = XMVector2Normalize(v);
				DirectX::XMStoreFloat2(&this->up, n);
				right.x = this->up.y;
				right.y = -this->up.x;
				rotation = atan2f(this->up.y, this->up.x);
			}
		}

		inline void setUp(float x, float y) {
			if (up.x != x || up.y != y) {
				auto v = DirectX::XMVectorSet(x, y, 0, 1);
				auto n = XMVector2Normalize(v);
				DirectX::XMStoreFloat2(&this->up, n);
				right.x = this->up.y;
				right.y = -this->up.x;
				rotation = atan2f(this->up.y, this->up.x);
			}
		}

		__declspec(property(get = getUp, put = setUp)) const XMFLOAT2& Up;

		inline XMFLOAT2 getRight() const {
			return right;
		}

		inline void setRight(const XMFLOAT2& right) {
			if (this->right.x != right.x || this->right.y != right.y) {
				auto v = DirectX::XMLoadFloat2(&right);
				auto n = XMVector2Normalize(v);
				DirectX::XMStoreFloat2(&this->right, n);
				up.x = this->right.y;
				up.y = -this->right.x;
				rotation = atan2f(this->up.y, this->up.x);
			}
		}

		inline void setRight(float x, float y) {
			if (right.x != x || right.y != y) {
				auto v = DirectX::XMVectorSet(x, y, 0, 1);
				auto n = XMVector2Normalize(v);
				DirectX::XMStoreFloat2(&this->right, n);
				up.x = this->right.y;
				up.y = -this->right.x;
				rotation = atan2f(this->up.y, this->up.x);
			}
		}

		__declspec(property(get = getRight, put = setRight)) const XMFLOAT2& Right;

		virtual void update(const Timer& timer) override;

#ifdef _DEBUG
		String print() const;
#endif
	};
}
