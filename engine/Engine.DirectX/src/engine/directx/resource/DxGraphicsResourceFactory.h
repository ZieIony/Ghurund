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
		virtual Mesh* makeMesh(const MeshData& meshData) override {
			auto mesh = makeIntrusive<DxMesh>();
			mesh->init(meshData, memoryManager);
			mesh->addReference();
			return mesh.get();
		}

		[[nodiscard]]
		virtual ITexture* makeTexture(Image& image, bool generateMips = false) override {
			auto texture = ghnew DxTexture();
			auto imagePtr = IntrusivePointer<Image>(&image);
			image.addReference();
			Array<IntrusivePointer<Image>> images = { imagePtr };
			texture->init(images, memoryManager);
			return texture;
		}

		[[nodiscard]]
		virtual ITexture* makeTexture(Array<IntrusivePointer<Image>>& images) override {
			auto texture = ghnew DxTexture();
			texture->init(images, memoryManager);
			return texture;
		}

		[[nodiscard]]
		virtual ICubeMap* makeCubemap(
			Ghurund::Core::Image& imageTop,
			Ghurund::Core::Image& imageBottom,
			Ghurund::Core::Image& imageLeft,
			Ghurund::Core::Image& imageRight,
			Ghurund::Core::Image& imageFront,
			Ghurund::Core::Image& imageBack
		) override {
			auto cubeMap = ghnew DxCubeMap();
			cubeMap->init(
				imageTop, imageBottom,
				imageLeft, imageRight,
				imageFront, imageBack,
				memoryManager
			);
			return cubeMap;
		}
	};
}
