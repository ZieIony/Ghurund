#pragma once

#include "core/object/RefCountedObject.h"
#include "core/math/Size.h"
#include "engine/parameter/ValueParameter.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class ParameterManager;

	class Camera:public Ghurund::Core::RefCountedObject {
	protected:
		IntSize viewSize;
		float aspectRatio, zNear, zFar;
		XMFLOAT4X4 view, proj, viewProj, viewProjInv;

		inline static const AString PARAMETER_NAME_FOV = "gh_fov";
		inline static const AString PARAMETER_NAME_ZNEAR = "gh_zNear";
		inline static const AString PARAMETER_NAME_ZFAR = "gh_zFar";
		inline static const AString PARAMETER_NAME_VIEW = "gh_view";
		inline static const AString PARAMETER_NAME_PROJECTION = "gh_projection";
		inline static const AString PARAMETER_NAME_VIEW_PROJECTION = "gh_viewProjection";
		inline static const AString PARAMETER_NAME_VIEW_PROJECTION_INV = "gh_viewProjectionInv";

		Float2Parameter* parameterFov = nullptr;
		FloatParameter* parameterZNear = nullptr, * parameterZFar = nullptr;
		MatrixParameter* parameterView = nullptr, * parameterProjection = nullptr;
		MatrixParameter* parameterViewProjection = nullptr, * parameterViewProjectionInv = nullptr;

	public:
		Camera():
			viewSize({ 640, 480 }),
			zNear(100.0f),
			zFar(200.0f) {
			parameterFov = ghnew Float2Parameter(PARAMETER_NAME_FOV);
			parameterZNear = ghnew FloatParameter(PARAMETER_NAME_ZNEAR);
			parameterZFar = ghnew FloatParameter(PARAMETER_NAME_ZFAR);

			parameterView = ghnew MatrixParameter(PARAMETER_NAME_VIEW);
			parameterProjection = ghnew MatrixParameter(PARAMETER_NAME_PROJECTION);
			parameterViewProjection = ghnew MatrixParameter(PARAMETER_NAME_VIEW_PROJECTION);
			parameterViewProjectionInv = ghnew MatrixParameter(PARAMETER_NAME_VIEW_PROJECTION_INV);
		}

		~Camera() {
			parameterFov->release();
			parameterZNear->release();
			parameterZFar->release();

			parameterView->release();
			parameterProjection->release();
			parameterViewProjection->release();
			parameterViewProjectionInv->release();
		}

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

		inline float getAspectRatio() const {
			return aspectRatio;
		}

		__declspec(property(get = getAspectRatio)) float AspectRatio;

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

		virtual void update() = 0;

		virtual void apply(ParameterManager& parameterManager) = 0;
	};
}
