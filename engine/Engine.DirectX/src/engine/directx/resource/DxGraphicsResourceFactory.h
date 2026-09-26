#pragma once

#include "engine/directx/mesh/DxMesh.h"
#include "engine/resource/IGraphicsResourceFactory.h"

namespace Ghurund::Engine::DirectX {
	class DxGraphicsResourceFactory:public IGraphicsResourceFactory {
	private:
		DxGraphics& graphics;
		CommandList& commandList;
		DxGPUMemoryManager& memoryManager;

	public:
		DxGraphicsResourceFactory(
			DxGPUMemoryManager& memoryManager,
			DxGraphics& graphics,
			CommandList& commandList
		):memoryManager(memoryManager), graphics(graphics), commandList(commandList) {
		}

		[[nodiscard]]
		virtual Mesh* makeMesh(const MeshData& meshData) override {
			auto mesh = makeIntrusive<DxMesh>();
			mesh->init(meshData, memoryManager);
			mesh->addReference();
			return mesh.get();
		}

		// TODO: replace ITextureFactory with this
		[[nodiscard]]
		virtual ITexture* makeTexture(Image& image) override {
			auto texture = ghnew DxTexture();
			texture->init(graphics, commandList, image);
			return texture;
		}
	};
}
