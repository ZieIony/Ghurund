#pragma once

#include "core/object/RefCountedObject.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace ::DirectX;

	class ParameterManager;

	class ICamera:public Ghurund::Core::RefCountedObject {
	protected:
		XMFLOAT4X4 view, proj, viewProj, viewProjInv;

	public:
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
