#pragma once

#include "buffer/RenderTarget.h"
#include "engine/directx/SwapChain.h"
#include <engine/graphics/RenderingContext.h>
#include "mesh/DxMesh.h"
#include "material/DxMaterial.h"

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

		virtual void draw(Set<RenderGroup>& renderGroups, ParameterManager& parameterManager) override {
			Ghurund::Engine::DirectX::CommandList* commandList = swapChain->CurrentFrame.CommandList;
			for (auto& group : renderGroups) {
				// TODO: sort on insertion
				group.objects.sort([&](const DrawPacket& first, const DrawPacket& second) {
					return (first.position.z - second.position.z) * (int8_t)group.DrawOrder;
				});
				for (auto& packet : group.objects) {
					auto mesh = (DxMesh*)packet.mesh.get();
					auto material = (DxMaterial*)packet.material.get();
					// TODO: setup parameters
					material->set(*commandList, parameterManager);
					mesh->draw(*commandList, material->Layout);
				}
			}
		}
	};
}
