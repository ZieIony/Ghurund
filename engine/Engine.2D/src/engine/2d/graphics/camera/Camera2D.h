#pragma once

#include "core/math/Size.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/rendering/GlobalParameters.h"

#include <DirectXMath.h>
#include <DirectXCollision.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class Camera2D: public Camera {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Camera2D::GET_TYPE();
#pragma endregion

	private:
		XMFLOAT3 pos, right, up;
		BoundingOrientedBox boundingOrientedBox;

	public:
		Camera2D();

		virtual void update() override;

		virtual void apply(GlobalParameters& globalParameters) override;

		inline XMFLOAT2 getPosition() const {
			return { pos.x, pos.y };
		}

		__declspec(property(get = getPosition)) XMFLOAT2 Position;

		inline XMFLOAT2 getUp() const {
			return { up.x, up.y };
		}

		__declspec(property(get = getUp)) XMFLOAT2 Up;

		inline XMFLOAT2 getRight() const {
			return { right.x, right.y };
		}

		__declspec(property(get = getRight)) XMFLOAT2 Right;

		void setPositionUp(const XMFLOAT2& pos, const XMFLOAT2& up = XMFLOAT2(0, 1));

		inline float getRoll() const {
			return atan2f(right.y, right.x);
		}

		void setRoll(float rotation);

		__declspec(property(get = getRoll, put = setRoll)) float Roll;

		void rotate(float delta);
		void pan(float x, float y);

		/**
		* Returns a box that includes exactly the space this camera sees.
		**/
		const BoundingOrientedBox& getViewBox() const {
			return boundingOrientedBox;
		}

		__declspec(property(get = getViewBox)) const BoundingOrientedBox& ViewBox;
	};
}