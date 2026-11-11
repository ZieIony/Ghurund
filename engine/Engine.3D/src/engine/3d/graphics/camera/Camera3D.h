#pragma once

#include "core/math/Size.h"
#include "engine/graphics/Camera.h"

#include <DirectXMath.h>
#include <DirectXCollision.h>

namespace Ghurund::Engine::_3D {
	using namespace ::DirectX;

	class Camera3D: public Camera {
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
		XMFLOAT2 fov;
		float dist;
		bool pers;

	public:
		inline static const XMFLOAT3 DEFAULT_UP = { 0, 1, 0 };

		Camera3D();

		void calcMouseRay(const XMINT2& mousePos, XMFLOAT3& rayPos, XMFLOAT3& rayDir) const;

		virtual void update() override;

		virtual void apply(GlobalParameters& globalParameters) override;

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
