#pragma once

#include "BaseTransformComponent2D.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class TransformComponent2D:public BaseTransformComponent2D {
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

	protected:
		virtual XMFLOAT2 getPositionInternal() const override {
			return position;
		}

		virtual void setPositionInternal(float x, float y) override {
			position.x = x;
			position.y = y;
		}

		virtual float getRotationInternal() const override {
			return rotation;
		}

		virtual void setRotationInternal(float rotation) override {
			this->rotation = rotation;
		}

		virtual XMFLOAT2 getScaleInternal() const override {
			return scale;
		}

		virtual void setScaleInternal(float x, float y) override {
			scale.x = x;
			scale.y = y;
		}

	public:
		TransformComponent2D(NotNull<Entity2D> owner, World2D& world):BaseTransformComponent2D(owner, world) {}
	};
}
