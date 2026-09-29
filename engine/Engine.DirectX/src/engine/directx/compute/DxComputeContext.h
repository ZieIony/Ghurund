#pragma once

#include "CommandList.h"
#include "DxGraphics.h"

#include "core/object/IntrusivePointer.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxComputeContext {
	private:
		Ghurund::Engine::DirectX::DxGraphics& graphics;
		IntrusivePointer<CommandList> commandList;

	public:
		DxComputeContext(Ghurund::Engine::DirectX::DxGraphics& graphics):graphics(graphics) {
			commandList.set(ghnew CommandList());
			commandList->init(graphics, graphics.ComputeQueue);
		}

		void generateMipMaps() {
			commandList->reset();
			commandList->finish();
		}
	};
}
