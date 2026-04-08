#pragma once

#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/2d/IGraphics2DContext.h"
#include <engine/directx/memory/DxGPUMemoryManager.h>
#include <engine/graphics/mesh/SpriteMeshData.h>
#include <engine/directx/mesh/DxMesh.h>
#include <engine/2d/graphics/mesh/TileMapMeshData.h>
#include <engine/directx/shader/DxShader.h>

namespace Ghurund::Engine::_2D::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class DxGraphics2DContext:public IGraphics2DContext {
	private:
		DxGPUMemoryManager& memoryManager;
		ResourceManager& resourceManager;
		IntrusivePointer<SpriteMeshData> spriteMeshData;

	public:
		DxGraphics2DContext(
			DxGPUMemoryManager& memoryManager,
			ResourceManager& resourceManager,
			Ghurund::Core::CoroutineScheduler& coroutineScheduler
		):IGraphics2DContext(coroutineScheduler), memoryManager(memoryManager), resourceManager(resourceManager) {
			spriteMeshData = makeIntrusive<SpriteMeshData>();
			spriteMeshData->init();
		}

		virtual Mesh* makeSpriteMesh() override;

		virtual CoroutineTask<IntrusivePointer<Material>> makeSpriteMaterial() override;

		virtual Mesh* makeTileMapMesh(IntSize tileMapSize, Array<TileInfo>& tiles) override;

		virtual CoroutineTask<IntrusivePointer<Material>> makeTileMapMaterial() override;

		virtual CoroutineTask<IntrusivePointer<Material>> makeBoxVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/2d/box.xml"));
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeCapsuleVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/2d/capsule.xml"));
		}

		virtual CoroutineTask<IntrusivePointer<Material>> makeSegmentVisualizationMaterial() override {
			co_return co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/2d/segment.xml"));
		}
	};
}
