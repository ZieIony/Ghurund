#include "ghedxpch.h"
#include "DxRenderingContext.h"

namespace Ghurund::Engine::DirectX {
	void DxRenderingContext::onInit() {
		swapChain = ghnew Ghurund::Engine::DirectX::SwapChain();
		swapChain->init(graphics, window);
	}

	void DxRenderingContext::onUninit() {
		uninitDxRenderingContext();
	}

	void DxRenderingContext::startFrame() {
		swapChain->CurrentFrame.start();

		CommandList* commandList = swapChain->CurrentFrame.CommandList;
		graphics.DescriptorAllocator.set(commandList->get());   // TODO: set allocator properly
		stats.startFrame();
	}

	void DxRenderingContext::finishFrame() {
		stats.finishFrame();
		swapChain->CurrentFrame.finish();
		swapChain->present();
	}
	
	void DxRenderingContext::setSize(Ghurund::Core::IntSize size) {
		if (swapChain)
			swapChain->uninitBuffers();
		//bool result = __super::onSizeChangedEvent();
		if (swapChain && size.Width > 0 && size.Height > 0) {
			swapChain->resize(size);
			swapChain->initBuffers();
		}
	}
}

