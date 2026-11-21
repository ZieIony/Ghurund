#include "ghedxpch.h"
#include "DxRenderingContext.h"

#include "engine/directx/mesh/DxMesh.h"
#include "DxGraphicsShader.h"
#include <engine/directx/shader/DxConstantBuffer.h>
#include "DxObjectParametersBuffer.h"

namespace Ghurund::Engine::DirectX {
	void DxRenderingContext::onInit() {
		swapChain = ghnew Ghurund::Engine::DirectX::SwapChain();
		swapChain->init(graphics, window.Handle, window.Size, FRAME_COUNT);
		for (auto& item : globalParameters)
			item = memoryManager.makeConstantBuffer(sizeof(GlobalParameters));
		for (auto& item : objectParameters)
			item = (DxObjectParametersBuffer*)memoryManager.makeParametersBuffer(100);
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

	void DxRenderingContext::setParameters(uint32_t id, const ObjectParameters& parameters) {
		objectParameters[currentFrame]->setValue(parameters, id);
	}

	void DxRenderingContext::draw(RenderGroup& renderGroup, MaterialVariantType variantType) {
		auto commandList = swapChain->CurrentFrame.RenderCommandList;
		if (renderGroup.Camera) {
			GlobalParameters p;
			renderGroup.Camera->apply(p);
			globalParameters[currentFrame]->setValue(&p, sizeof(GlobalParameters), 0);
		}

		for (auto& batch : renderGroup.objects) {
			stats.materialChanges++;
			auto materialVariant = batch.value.material->getShader(variantType);
			materialVariant->applyInputs();
			auto shader = (DxGraphicsShader*)materialVariant;
			bool shaderChanged = shader->apply(*commandList, *globalParameters[currentFrame], *objectParameters[currentFrame]);
			stats.instancesRendered += batch.value.instances.Size;
			auto mesh = (DxMesh*)batch.value.mesh;
			mesh->draw(*commandList, shader->Layout, batch.value.instances);
			stats.modelsRendered++;	// this mesh could have been rendered earlier with another material already
		}
	}
}
