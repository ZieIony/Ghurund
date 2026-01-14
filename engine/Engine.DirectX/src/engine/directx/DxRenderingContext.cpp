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
		if (swapChain && size.Width > 0 && size.Height > 0) {
			swapChain->Size = size;
			swapChain->initBuffers();
		}
	}

	void DxRenderingContext::draw(Set<RenderGroup>& renderGroups, ParameterManager& parameterManager) {
		Ghurund::Engine::DirectX::CommandList* commandList = swapChain->CurrentFrame.CommandList;
		for (auto& group : renderGroups) {
			// TODO: sort on insertion
			group.objects.sort([&](const DrawPacket& first, const DrawPacket& second) {
				return (first.position.z - second.position.z) * (int8_t)group.DrawOrder;
			});
			for (auto& packet : group.objects) {
				auto mesh = (DxMesh*)packet.mesh.get();
				auto material = packet.material.get();
				material->applyInputs(parameterManager.Parameters);
				auto shader = (DxShader*)material->Shader;
				shader->set(*commandList);
				mesh->draw(*commandList, shader->Layout);
			}
		}
	}
}

