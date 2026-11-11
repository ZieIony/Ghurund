#pragma once

#include "engine/directx/buffer/RenderTarget.h"
#include "engine/directx/SwapChain.h"
#include "engine/directx/CommandList.h"
#include "engine/graphics/rendering/RenderingContext.h"
#include "engine/directx/shader/DxConstantBuffer.h"

namespace Ghurund::Engine::DirectX {
	class DxRenderingContext: public RenderingContext {
	private:
		SwapChain* swapChain = nullptr;
		Ghurund::Engine::DirectX::DxGraphics& graphics;
		DxGPUMemoryManager& memoryManager;
		DxConstantBuffer* globalParametersCB = nullptr;

		inline void uninitDxRenderingContext() {
			safeRelease(globalParametersCB);
			delete swapChain;
			swapChain = nullptr;
		}

	protected:
		virtual void onInit() override;

		virtual void onDeinit() override;

	public:
		DxRenderingContext(SystemWindow& window, Ghurund::Engine::DirectX::DxGraphics& graphics, DxGPUMemoryManager& memoryManager)
			:Ghurund::Engine::RenderingContext(window), graphics(graphics), memoryManager(memoryManager) {}

		~DxRenderingContext() {
			uninitDxRenderingContext();
		}

		virtual void startFrame() override;

		virtual void finishFrame() override;

		inline void startFrame(CommandList& commandList) {
			swapChain->CurrentFrame.startFrame(commandList);
		}

		virtual void clear(const Ghurund::Core::Color* clearColor) override {
			swapChain->CurrentFrame.clear(clearColor);
			graphics.DescriptorAllocator.set(swapChain->CurrentFrame.RenderCommandList->get());   // TODO: apply allocator properly
		}

		virtual void setSize(Ghurund::Core::IntSize size) override;

		virtual void draw(RenderGroup& renderGroup, MaterialVariantType variantType) override;
	};
}
