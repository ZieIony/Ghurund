#pragma once

#include "engine/directx/DirectXDrawingContext.h"
#include "RenderTarget2D.h"

namespace Ghurund::UI::Direct2D {
	using namespace Ghurund::Engine::DirectX;

	class Direct2DDrawingContext:public DirectXDrawingContext {
	private:
		RenderTarget2D& target2d;

	public:
		Direct2DDrawingContext(Ghurund::Engine::DirectX::RenderTarget& renderTarget, RenderTarget2D& target2d)
			:DirectXDrawingContext(renderTarget), target2d(target2d) {}

		inline RenderTarget2D& getRenderTarget2D() {
			return target2d;
		}

		__declspec(property(get = getRenderTarget2D)) RenderTarget2D& RenderTarget2D;
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::Direct2D::Direct2DDrawingContext>();
}