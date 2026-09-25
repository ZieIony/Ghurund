#pragma once

#include "engine/directx/mesh/DxMesh.h"
#include "engine/resource/IGraphicsResourceFactory.h"

namespace Ghurund::Engine::DirectX {
	class DxGraphicsResourceFactory:public IGraphicsResourceFactory {
	private:
		DxGPUMemoryManager& memoryManager;

	public:
		DxGraphicsResourceFactory(DxGPUMemoryManager& memoryManager):memoryManager(memoryManager) {}

		[[nodiscard]]
		virtual Mesh* makeMesh(const MeshData& meshData) override {
			auto mesh = makeIntrusive<DxMesh>();
			mesh->init(meshData, memoryManager);
			mesh->addReference();
			return mesh.get();
		}
	};
}
