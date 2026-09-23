#pragma once

#include "engine/graphics/material/Material.h"
#include "engine/3d/IGraphics3DContext.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"
#include "engine/graphics/mesh/SpriteMeshData.h"

namespace Ghurund::Engine::_3D::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class DxGraphics3DContext:public IGraphics3DContext {
	private:
		DxGPUMemoryManager& memoryManager;
		ResourceManager& resourceManager;
		IntrusivePointer<SpriteMeshData> spriteMeshData;

	public:
		DxGraphics3DContext(
			DxGPUMemoryManager& memoryManager,
			ResourceManager& resourceManager
		):memoryManager(memoryManager), resourceManager(resourceManager) {
			spriteMeshData = makeIntrusive<SpriteMeshData>();
			spriteMeshData->init();
		}

		virtual CoroutineTask<IntrusivePointer<Mesh>> makeQuadMesh() override;

		virtual CoroutineTask<IntrusivePointer<Material>> makeBoxVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/box.xml"));
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeCapsuleVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/capsule.xml"));
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeSegmentVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/segment.xml"));
		}
	};
}
