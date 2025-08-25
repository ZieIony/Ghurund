#pragma once

#include "buffer/RenderTarget.h"
#include "engine/directx/SwapChain.h"
#include <engine/graphics/RenderingContext.h>

namespace Ghurund::Engine::DirectX {
	class DxRenderingContext: public RenderingContext {
	private:
		SwapChain* swapChain = nullptr;
		Ghurund::Engine::DirectX::DxGraphics* graphics;

		inline void uninitDxRenderingContext() {
			delete swapChain;
			swapChain = nullptr;
		}

	protected:
		virtual void onInit() override;

		virtual void onUninit() override;

	public:
		DxRenderingContext(Ghurund::Core::NotNull<SystemWindow> window, NotNull<Ghurund::Engine::DirectX::DxGraphics> graphics)
			:Ghurund::Engine::RenderingContext(window), graphics(&graphics) {}

		~DxRenderingContext() {
			uninitDxRenderingContext();
		}

		virtual void startFrame() override;

		virtual void finishFrame() override;
		
		virtual void clear(const Ghurund::Core::Color* clearColor) override {
			swapChain->CurrentFrame.clear(clearColor);
		}

		virtual void setSize(Ghurund::Core::IntSize size) override;

		inline SwapChain& getSwapChain() {
			return *swapChain;
		}

		__declspec(property(get = getSwapChain)) Ghurund::Engine::DirectX::SwapChain& SwapChain;

		void paint() {
			startFrame();
			Ghurund::Engine::DirectX::CommandList& commandList = swapChain->CurrentFrame.CommandList;
			Color clearColor = { 0xff1f1f1f };
			clear(&clearColor);
			//levelManager.draw(commandList);
			swapChain->CurrentFrame.flush();
			//auto drawingContext = DirectXDrawingContext(frame.RenderTarget);
			//Layers.draw(drawingContext);
			finishFrame();
		}
	};
}
