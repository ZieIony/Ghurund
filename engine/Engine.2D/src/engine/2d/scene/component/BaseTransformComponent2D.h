#pragma once

#include "engine/2d/scene/component/Component2DGroup.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class BaseTransformComponent2D:public Component2DGroup {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = BaseTransformComponent2D::GET_TYPE();
#pragma endregion

	protected:
		XMFLOAT4X4 localTransformation;
		XMFLOAT4X4 worldTransformation;

		virtual XMFLOAT2 getPositionInternal() const = 0;

		virtual void setPositionInternal(float x, float y) = 0;

		virtual float getRotationInternal() const = 0;

		virtual void setRotationInternal(float rotation) = 0;

		virtual XMFLOAT2 getScaleInternal() const = 0;

		virtual void setScaleInternal(float x, float y) = 0;

	public:
		inline const XMFLOAT4X4& getLocalTransformation() const {
			return localTransformation;
		}

		__declspec(property(get = getLocalTransformation)) const XMFLOAT4X4& LocalTransformation;

		inline XMFLOAT2 getPosition() const {
			return getPositionInternal();
		}

		inline void setPosition(const XMFLOAT2& pos) {
			setPositionInternal(pos.x, pos.y);
		}

		inline void setPosition(float x, float y) {
			setPositionInternal(x, y);
		}

		__declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

		inline float getRotation() const {
			return getRotationInternal();
		}

		inline void setRotation(float rotation) {
			setRotationInternal(rotation);
		}

		__declspec(property(get = getRotation, put = setRotation)) float Rotation;

		inline void setScale(const XMFLOAT2& scale) {
			setScaleInternal(scale.x, scale.y);
		}

		inline void setScale(float x, float y) {
			setScaleInternal(x, y);
		}

		inline XMFLOAT2 getScale() const {
			return getScaleInternal();
		}

		__declspec(property(get = getScale, put = setScale)) const XMFLOAT2& Scale;

		virtual void update(const XMFLOAT4X4& parentTransformation, const Timer& timer) override;

#ifdef _DEBUG
		virtual String printTree() const;
#endif
	};
}
