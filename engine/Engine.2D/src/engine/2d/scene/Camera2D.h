#pragma once

#include "core/math/Size.h"
#include <core/resource/LoadOption.h>
#include <core/resource/SaveOption.h>
#include "engine/graphics/ICamera.h"
#include "engine/parameter/ParameterCollection.h"
#include "engine/parameter/ValueParameter.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class Camera2D: public ICamera {
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
		float zNear, zFar;
		XMFLOAT4X4 view, proj, viewProj, viewProjInv;
		IntSize viewSize;

		inline static const AString CAMERA_POSITION = "cameraPosition";
		inline static const AString CAMERA_UP = "cameraUp";
		inline static const AString CAMERA_RIGHT = "cameraRight";
		inline static const AString ZNEAR = "zNear";
		inline static const AString ZFAR = "zFar";
		inline static const AString VIEW = "view";
		inline static const AString PROJECTION = "projection";
		inline static const AString VIEW_PROJECTION = "viewProjection";
		inline static const AString VIEW_PROJECTION_INV = "viewProjectionInv";

		Float3Parameter* parameterPosition = nullptr, * parameterUp = nullptr, * parameterRight = nullptr;
		FloatParameter* parameterZNear = nullptr, * parameterZFar = nullptr;
		MatrixParameter* parameterView = nullptr, * parameterProjection = nullptr;
		MatrixParameter* parameterViewProjection = nullptr, * parameterViewProjectionInv = nullptr;

	protected:
		virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
		virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

	public:
		Camera2D();

		~Camera2D();

		virtual void apply(ParameterManager& parameterManager) override;

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

		inline const XMFLOAT4X4& getView() const {
			return view;
		}

		__declspec(property(get = getView)) XMFLOAT4X4& View;

		inline const XMFLOAT4X4& getProjection() const {
			return proj;
		}

		__declspec(property(get = getProjection)) XMFLOAT4X4& Projection;

		inline const XMFLOAT4X4& getViewProjection() const {
			return viewProj;
		}

		__declspec(property(get = getViewProjection)) XMFLOAT4X4& ViewProjection;

		inline const XMFLOAT4X4& getViewProjectionInv() const {
			return viewProjInv;
		}

		__declspec(property(get = getViewProjectionInv)) XMFLOAT4X4& ViewProjectionInv;

		void setPositionUp(const XMFLOAT2& pos, const XMFLOAT2& up = XMFLOAT2(0, 1));

		inline float getRoll() const {
			return atan2f(right.y, right.x);
		}

		void setRoll(float rotation);

		__declspec(property(get = getRoll, put = setRoll)) float Roll;

		void rotate(float delta);
		void pan(float x, float y);
	};
}