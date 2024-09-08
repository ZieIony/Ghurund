#pragma once

#include "core/application/DrawingContext.h"
#include "RenderTarget2D.h"

namespace Ghurund::UI::Direct2D {
	class DrawingContext:public IDrawingContext {
	private:
		RenderTarget2D* target2d;

	public:
		RenderTarget2D& getRenderTarget() {
			return *target2d;
		}

		__declspec(property(get = getRenderTarget)) RenderTarget2D& RenderTarget;
	};
}