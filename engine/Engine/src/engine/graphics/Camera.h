#pragma once

#include "core/object/RefCountedObject.h"
#include "core/math/Size.h"
#include "engine/graphics/rendering/GlobalParameters.h"

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

	public:
		Camera():
			viewSize({ 640, 480 }),
			zNear(100.0f),
			zFar(200.0f) {
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

		virtual void apply(GlobalParameters& globalParameters) = 0;
	};
}
