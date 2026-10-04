#pragma once

#include "core/math/Size.h"
#include "engine/graphics/ICamera.h"
#include "engine/parameter/ValueParameter.h"

#include <DirectXMath.h>
#include <DirectXCollision.h>

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
		XMFLOAT2 fov;
		float aspectRatio, zNear, zFar, dist;
		bool pers;

		inline static const AString PARAMETER_NAME_DIRECTION = "gh_cameraDirection";
		inline static const AString PARAMETER_NAME_POSITION = "gh_cameraPosition";
		inline static const AString PARAMETER_NAME_TARGET = "gh_cameraTarget";
		inline static const AString PARAMETER_NAME_UP = "gh_cameraUp";
		inline static const AString PARAMETER_NAME_RIGHT = "gh_cameraRight";
		inline static const AString PARAMETER_NAME_FOV = "gh_fov";
		inline static const AString PARAMETER_NAME_ZNEAR = "gh_zNear";
		inline static const AString PARAMETER_NAME_ZFAR = "gh_zFar";
		inline static const AString PARAMETER_NAME_VIEW = "gh_view";
		inline static const AString PARAMETER_NAME_PROJECTION = "gh_projection";
		inline static const AString PARAMETER_NAME_VIEW_PROJECTION = "gh_viewProjection";
		inline static const AString PARAMETER_NAME_VIEW_PROJECTION_INV = "gh_viewProjectionInv";

		Float3Parameter* parameterDirection = nullptr, * parameterPosition = nullptr, * parameterTarget = nullptr;
		Float3Parameter* parameterUp = nullptr, * parameterRight = nullptr;
		Float2Parameter* parameterFov = nullptr;
		FloatParameter* parameterZNear = nullptr, * parameterZFar = nullptr;
		MatrixParameter* parameterView = nullptr, * parameterProjection = nullptr;
		MatrixParameter* parameterViewProjection = nullptr, * parameterViewProjectionInv = nullptr;

	public:
		inline static const XMFLOAT3 DEFAULT_UP = { 0, 1, 0 };

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
#ifdef _DEBUG
			_ASSERT(viewSize.Width > 0 && viewSize.Height > 0);
#endif
			this->viewSize = viewSize;
			aspectRatio = (float)viewSize.Width / (float)viewSize.Height;
		}

		inline void setViewSize(uint32_t w, uint32_t h) {
#ifdef _DEBUG
			_ASSERT(w > 0 && h > 0);
#endif
			viewSize.Width = w;
			viewSize.Height = h;
			aspectRatio = (float)viewSize.Width / (float)viewSize.Height;
		}

		__declspec(property(get = getViewSize, put = setViewSize)) IntSize& ViewSize;

		inline void setFOV(float verticalFOVRad) {
#ifdef _DEBUG
			_ASSERT(verticalFOVRad > 0 && verticalFOVRad < XM_PI / 2.0f);
#endif
			fov.x = 2.0f * atan(tan(verticalFOVRad * 0.5f) / aspectRatio);
			fov.y = verticalFOVRad;
		}

		inline void setFOV(const XMFLOAT2& fov) {
#ifdef _DEBUG
			_ASSERT(fov.x > 0 && fov.x < XM_PI / 2.0f && fov.y > 0 && fov.y < XM_PI / 2.0f);
#endif
			this->fov = fov;
		}

		inline const XMFLOAT2& getFOV() const {
			return fov;
		}

		__declspec(property(get = getFOV, put = setFOV)) const XMFLOAT2& FOV;

		inline float getAspectRatio() const {
			return aspectRatio;
		}

		__declspec(property(get = getAspectRatio)) float AspectRatio;

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

		/**
		* Sets camera position, direction, target, right and up vectors so that it looks at
		* the bounding sphere. The sphere should be transformed to world coordinates.
		**/
		void setDirectionSphereUp(const XMFLOAT3& dir, const BoundingSphere& boundingSphere, const XMFLOAT3& up);

		/**
		* Sets camera position, direction, target, right and up vectors so that it looks at
		* the bounding box. The box should be transformed to world coordinates.
		**/
		void setDirectionBoxUp(const XMFLOAT3& dir, const BoundingBox& boundingBox, const XMFLOAT3& up = DEFAULT_UP);

		/**
		* Sets camera position, direction, target, right and up vectors so that it looks at
		* the bounding box. The box should be transformed to world coordinates.
		**/
		void setDirectionBoxUp(const XMFLOAT3& dir, const BoundingOrientedBox& boundingBox, const XMFLOAT3& up = DEFAULT_UP);

		void setPositionTargetUp(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up = DEFAULT_UP);
		void setPositionDirectionDistanceUp(const XMFLOAT3& pos, const XMFLOAT3& dir, float dist, const XMFLOAT3& up = DEFAULT_UP);

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
		// move by d * direction, r * right, and u * up
		void move(float d, float r, float u = 0.0f);
		void zoom(float z);
	};
}
