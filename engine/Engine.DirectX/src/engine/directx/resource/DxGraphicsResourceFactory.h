#pragma once

#include "engine/directx/cubemap/DxCubeMap.h"
#include "engine/directx/mesh/DxMesh.h"
#include "engine/directx/texture/DxTexture.h"
#include "engine/resource/IGraphicsResourceFactory.h"

namespace Ghurund::Engine::DirectX {
	class DxGraphicsResourceFactory:public IGraphicsResourceFactory {
	private:
		DxGPUMemoryManager& memoryManager;
		DxGraphics& graphics;

	public:
		DxGraphicsResourceFactory(
			DxGPUMemoryManager& memoryManager, DxGraphics& graphics
		):memoryManager(memoryManager), graphics(graphics) {
		}

		[[nodiscard]]
		virtual Mesh* makeMesh(NotNull<MeshData> meshData) override {
			auto mesh = makeIntrusive<DxMesh>();
			mesh->Data = meshData.get();
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
			texture->init(memoryManager, graphics);
			return texture;
		}

		[[nodiscard]]
		virtual ITexture* makeTexture(List<IntrusivePointer<Image>>& images) override {
			auto texture = ghnew DxTexture();
			texture->Images = images;
			texture->init(memoryManager, graphics);
			return texture;
		}
	};
}
