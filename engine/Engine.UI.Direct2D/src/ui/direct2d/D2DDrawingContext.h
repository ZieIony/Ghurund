#pragma once

#include "RenderTarget2D.h"

namespace Ghurund::UI::Direct2D {
	class D2DDrawingContext:public IDrawingContext {
	public:
		RenderTarget& renderTarget;

		D2DDrawingContext(RenderTarget& renderTarget):renderTarget(renderTarget) {}
	};
}