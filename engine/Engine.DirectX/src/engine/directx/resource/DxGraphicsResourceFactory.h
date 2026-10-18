#pragma once

#include "engine/directx/cubemap/DxCubeMap.h"
#include "engine/directx/mesh/DxMesh.h"
#include "engine/directx/texture/DxTexture.h"
#include "engine/resource/IGraphicsResourceFactory.h"

namespace Ghurund::Engine::DirectX {
	class DxGraphicsResourceFactory:public IGraphicsResourceFactory {
	private:
		DxGPUMemoryManager& memoryManager;

	public:
		DxGraphicsResourceFactory(
			DxGPUMemoryManager& memoryManager
		):memoryManager(memoryManager) {
		}

		[[nodiscard]]
		virtual Mesh* makeMesh(NotNull<MeshData> meshData) override {
			auto mesh = makeIntrusive<DxMesh>();
			mesh->setMeshData(meshData.get());
			mesh->init(memoryManager);
			mesh->addReference();
			return mesh.get();
		}

		[[nodiscard]]
		virtual ITexture* makeTexture(Image& image, bool generateMips = false) override {
			auto texture = ghnew DxTexture();
			auto imagePtr = IntrusivePointer<Image>(&image);
			image.addReference();
			List<IntrusivePointer<Image>> images = { imagePtr };
			texture->Images = images;
			texture->init(memoryManager);
			return texture;
		}

		[[nodiscard]]
		virtual ITexture* makeTexture(List<IntrusivePointer<Image>>& images) override {
			auto texture = ghnew DxTexture();
			texture->Images = images;
			texture->init(memoryManager);
			return texture;
		}
	};
}
