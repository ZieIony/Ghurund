#pragma once

#include "buffer/RenderTarget.h"
#include "engine/directx/SwapChain.h"
#include "engine/graphics/rendering/RenderingContext.h"
#include "mesh/DxMesh.h"
#include "shader/DxShader.h"

namespace Ghurund::Engine::DirectX {
	class DxRenderingContext: public RenderingContext {
	private:
		SwapChain* swapChain = nullptr;
		Ghurund::Engine::DirectX::DxGraphics& graphics;

		inline void uninitDxRenderingContext() {
			delete swapChain;
			swapChain = nullptr;
		}

	protected:
		virtual void onInit() override;

		virtual void onUninit() override;

	public:
		DxRenderingContext(SystemWindow& window, Ghurund::Engine::DirectX::DxGraphics& graphics)
			:Ghurund::Engine::RenderingContext(window), graphics(graphics) {}

		~DxRenderingContext() {
			uninitDxRenderingContext();
		}

		virtual void startFrame() override;

		virtual void finishFrame() override;
		
		virtual void clear(const Ghurund::Core::Color* clearColor) override {
			swapChain->CurrentFrame.clear(clearColor);
		}

		virtual void setSize(Ghurund::Core::IntSize size) override;

		virtual void draw(Set<RenderGroup>& renderGroups, ParameterManager& parameterManager) override;
	};
}
