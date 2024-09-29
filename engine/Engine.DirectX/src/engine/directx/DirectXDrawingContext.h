#pragma once

#include "buffer/RenderTarget.h"

namespace Ghurund::Engine::DirectX {
	class DirectXDrawingContext {
	private:
		RenderTarget& renderTarget;

	public:
		DirectXDrawingContext(RenderTarget& renderTarget):renderTarget(renderTarget) {}

		virtual ~DirectXDrawingContext() {}

		inline RenderTarget& getRenderTarget() {
			return renderTarget;
		}

		__declspec(property(get = getRenderTarget)) RenderTarget& RenderTarget;
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::Engine::DirectX::DirectXDrawingContext>();
}