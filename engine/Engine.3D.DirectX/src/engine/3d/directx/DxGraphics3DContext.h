#pragma once

#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/3d/IGraphics3DContext.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"
#include "engine/graphics/mesh/SpriteMeshData.h"
#include "engine/directx/mesh/DxMesh.h"
#include "engine/directx/shader/DxShader.h"

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

		virtual CoroutineTask<IntrusivePointer<Material>> makeBoxVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/3d/box.xml"));
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeCapsuleVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/3d/capsule.xml"));
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeSegmentVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/3d/segment.xml"));
		}
	};
}
