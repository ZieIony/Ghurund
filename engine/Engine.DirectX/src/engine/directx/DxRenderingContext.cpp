#include "ghedxpch.h"
#include "DxRenderingContext.h"

namespace Ghurund::Engine::DirectX {
	void DxRenderingContext::onInit() {
		swapChain = ghnew Ghurund::Engine::DirectX::SwapChain();
		swapChain->init(graphics, window.Handle, window.Size);
	}

	void DxRenderingContext::onUninit() {
		uninitDxRenderingContext();
	}

	void DxRenderingContext::startFrame() {
		swapChain->CurrentFrame.start();

		CommandList* commandList = swapChain->CurrentFrame.CommandList;
		graphics.DescriptorAllocator.set(commandList->get());   // TODO: apply allocator properly
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
		if (swapChain && size.Width > 0 && size.Height > 0) {
			swapChain->Size = size;
			swapChain->initBuffers();
		}
	}

	void DxRenderingContext::draw(Set<RenderGroup>& renderGroups, ParameterManager& parameterManager) {
		Ghurund::Engine::DirectX::CommandList* commandList = swapChain->CurrentFrame.CommandList;
		for (auto& group : renderGroups) {
			if (group.Camera)
				group.Camera->apply(parameterManager);

			// TODO: sort on insertion
			group.objects.sort([&](const DrawPacket& first, const DrawPacket& second) -> bool {
				return (first.Order - second.Order) * (int8_t)group.DrawOrder > 0;
			});
			for (auto& packet : group.objects) {
				auto mesh = (DxMesh*)packet.Mesh;
				auto material = packet.Material;
				material->applyInputs(parameterManager.Parameters);
				auto shader = (DxShader*)material->Shader;
				bool shaderChanged = shader->apply(*commandList);
				mesh->draw(*commandList, shader->Layout);

				stats.modelsRendered++;
				if (shaderChanged)
					stats.materialChanges++;
			}
		}
	}
}

