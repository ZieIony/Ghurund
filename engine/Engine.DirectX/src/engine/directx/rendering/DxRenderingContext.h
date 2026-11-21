#pragma once

#include "DxObjectParametersBuffer.h"
#include "IdStreamFactory.h"

#include "engine/directx/CommandList.h"
#include "engine/directx/shader/DxConstantBuffer.h"
#include "engine/directx/SwapChain.h"
#include "engine/graphics/rendering/RenderingContext.h"

namespace Ghurund::Engine::DirectX {
	class DxRenderingContext: public RenderingContext {
	private:
		static inline const uint32_t FRAME_COUNT = 2;

		SwapChain* swapChain = nullptr;
		Ghurund::Engine::DirectX::DxGraphics& graphics;
		IdStreamFactory idStreamFactory;
		DxGPUMemoryManager& memoryManager;
		Array<DxConstantBuffer*> globalParameters = FRAME_COUNT;
		Array<DxObjectParametersBuffer*> objectParameters = FRAME_COUNT;
		uint32_t currentFrame = 0;

		inline void uninitDxRenderingContext() {
			for (auto& item : globalParameters)
				safeRelease(item);
			for (auto& item : objectParameters)
				delete item;
			delete swapChain;
			swapChain = nullptr;
		}

	protected:
		virtual void onInit() override;

		virtual void onDeinit() override;

	public:
		DxRenderingContext(SystemWindow& window, Ghurund::Engine::DirectX::DxGraphics& graphics, DxGPUMemoryManager& memoryManager)
			:Ghurund::Engine::RenderingContext(window), graphics(graphics), memoryManager(memoryManager), idStreamFactory(memoryManager) {}

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

		virtual void setParameters(uint32_t id, const ObjectParameters& parameters) override;

		virtual void draw(RenderGroup& renderGroup, MaterialVariantType variantType) override;
	};
}
