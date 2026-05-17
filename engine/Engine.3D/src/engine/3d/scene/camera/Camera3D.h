#pragma once

#include "core/math/Size.h"
#include "engine/graphics/ICamera.h"
#include "engine/parameter/ValueParameter.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_3D {
	using namespace ::DirectX;

	class Camera3D: public ICamera {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Camera3D::GET_TYPE();
#pragma endregion

	private:
		XMFLOAT3 pos, target, dir, right, up;
		//XMFLOAT4X4 facing;
		IntSize viewSize;
		float fov, zNear, zFar, dist;
		bool pers;

		inline static const AString CAMERA_DIRECTION = "cameraDirection";
		inline static const AString CAMERA_POSITION = "cameraPosition";
		inline static const AString CAMERA_TARGET = "cameraTarget";
		inline static const AString CAMERA_UP = "cameraUp";
		inline static const AString CAMERA_RIGHT = "cameraRight";
		inline static const AString FOV = "fov";
		inline static const AString ZNEAR = "zNear";
		inline static const AString ZFAR = "zFar";
		inline static const AString VIEW = "view";
		inline static const AString PROJECTION = "projection";
		inline static const AString VIEW_PROJECTION = "viewProjection";
		inline static const AString VIEW_PROJECTION_INV = "viewProjectionInv";

		Float3Parameter* parameterDirection = nullptr, * parameterPosition = nullptr, * parameterTarget = nullptr;
		Float3Parameter* parameterUp = nullptr, * parameterRight = nullptr;
		FloatParameter* parameterFov = nullptr;
		FloatParameter* parameterZNear = nullptr, * parameterZFar = nullptr;
		MatrixParameter* parameterView = nullptr, * parameterProjection = nullptr;
		MatrixParameter* parameterViewProjection = nullptr, * parameterViewProjectionInv = nullptr;

	public:
		Camera3D();

		~Camera3D();

		void calcMouseRay(const XMINT2& mousePos, XMFLOAT3& rayPos, XMFLOAT3& rayDir) const;

		virtual void update() override;

		virtual void apply(ParameterManager& parameterManager) override;

		inline const XMFLOAT3& getPosition() const {
			return pos;
		}

		__declspec(property(get = getPosition)) XMFLOAT3& Position;

		inline const XMFLOAT3& getUp() const {
			return up;
		}

		__declspec(property(get = getUp)) XMFLOAT3& Up;

		inline const XMFLOAT3& getTarget() const {
			return target;
		}

		__declspec(property(get = getTarget)) XMFLOAT3& Target;

		inline const XMFLOAT3& getDirection() const {
			return dir;
		}

		__declspec(property(get = getDirection)) XMFLOAT3& Direction;

		inline const XMFLOAT3& getRight() const {
			return right;
		}

		__declspec(property(get = getRight)) XMFLOAT3& Right;


		inline const IntSize& getViewSize() const {
			return viewSize;
		}

		inline void setViewSize(const IntSize& viewSize) {
			this->viewSize = viewSize;
		}

		inline void setViewSize(uint32_t w, uint32_t h) {
			viewSize = IntSize(w, h);
		}

		__declspec(property(get = getViewSize, put = setViewSize)) IntSize& ViewSize;

		inline float getAspect() const {
			return (float)viewSize.Width / (float)viewSize.Height;
		}

		__declspec(property(get = getAspect)) float Aspect;

		inline float getDistance() const {
			return dist;
		}

		__declspec(property(get = getDistance)) float Distance;

/*		inline const XMFLOAT4X4& getFacing() const {
			return facing;
		}

		__declspec(property(get = getFacing)) XMFLOAT4X4& Facing;*/

		inline bool getPerspective() const {
			return pers;
		}

		inline void setPerspective(bool pers) {
			this->pers = pers;
		}

		__declspec(property(get = getPerspective, put = setPerspective)) bool Perspective;

		void setPositionTargetUp(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up = XMFLOAT3(0, 1, 0));
		void setPositionDirectionDistanceUp(const XMFLOAT3& pos, const XMFLOAT3& dir, float dist = 1.0f, const XMFLOAT3& up = XMFLOAT3(0, 1, 0));

		inline XMFLOAT3 getRotation() const {
			float currentYaw = (float)(atan2(dir.x, dir.z) + XM_PI);
			float currentPitch = atan2f(dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z));
			float currentRoll = atan2f(right.y, 1);

			return XMFLOAT3(currentYaw, currentPitch, currentRoll);
		}

		void setRotation(float yaw, float pitch, float roll = 0.0f);
		void setOrbit(float yaw, float pitch, float roll = 0.0f);
		void rotate(float yaw, float pitch, float roll = 0.0f);
		void orbit(float yaw, float pitch, float roll = 0.0f);
		void pan(float x, float y);
		void zoom(float z);
	};
}