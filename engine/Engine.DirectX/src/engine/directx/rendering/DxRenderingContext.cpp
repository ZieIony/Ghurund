#include "ghedxpch.h"
#include "DxRenderingContext.h"

#include "engine/directx/mesh/DxMesh.h"
#include "DxGraphicsShader.h"
#include <engine/directx/shader/DxConstantBuffer.h>

namespace Ghurund::Engine::DirectX {
	void DxRenderingContext::onInit() {
		swapChain = ghnew Ghurund::Engine::DirectX::SwapChain();
		swapChain->init(graphics, window.Handle, window.Size);
		globalParametersCB = memoryManager.makeConstantBuffer(sizeof(GlobalParameters));
	}

	inline void deinit() {
	}

	void DxRenderingContext::onDeinit() {
		uninitDxRenderingContext();
	}

	void DxRenderingContext::startFrame() {
		swapChain->CurrentFrame.start();

		graphics.DescriptorAllocator.set(swapChain->CurrentFrame.StartCommandList->get());   // TODO: apply allocator properly
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
		__super::setSize(size);
		if (swapChain && size.Width > 0 && size.Height > 0) {
			swapChain->Size = size;
			swapChain->initBuffers();
		}
	}

	void DxRenderingContext::draw(RenderGroup& renderGroup, MaterialVariantType variantType) {
		auto commandList = swapChain->CurrentFrame.RenderCommandList;
		if (renderGroup.Camera)
			renderGroup.Camera->apply(globalParameters);
		globalParametersCB->setValue(&globalParameters, sizeof(GlobalParameters), 0);

		// TODO: sort on insertion
		renderGroup.objects.sort([&](const DrawPacket& first, const DrawPacket& second) -> bool {
			return (first.Order - second.Order) * (int8_t)renderGroup.DrawGroup.DrawOrder > 0;
		});
		for (auto& packet : renderGroup.objects) {
			auto mesh = (DxMesh*)packet.Mesh;
			auto materialVariant = packet.Material->getShader(variantType);
			materialVariant->applyInputs();
			auto shader = (DxGraphicsShader*)materialVariant;
			bool shaderChanged = shader->apply(*commandList);
			globalParametersCB->set(*commandList, 0);
			mesh->draw(*commandList, shader->Layout);

			stats.modelsRendered++;
			if (shaderChanged)
				stats.materialChanges++;
		}
	}
}
