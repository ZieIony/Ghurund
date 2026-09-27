#pragma once

#include "engine/directx/mesh/DxMesh.h"
#include "engine/resource/IGraphicsResourceFactory.h"
#include "engine/directx/cubemap/DxCubeMap.h"

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
		virtual ITexture* makeTexture(Image& image) override {
			auto texture = ghnew DxTexture();
			texture->init(image, memoryManager);
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
