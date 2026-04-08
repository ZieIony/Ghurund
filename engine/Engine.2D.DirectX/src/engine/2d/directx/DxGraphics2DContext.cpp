#include "ghe2ddxpch.h"
#include "DxGraphics2DContext.h"

namespace Ghurund::Engine::_2D::DirectX {
	Mesh* DxGraphics2DContext::makeSpriteMesh() {
		auto mesh = makeIntrusive<DxMesh>();
		mesh->init(spriteMeshData.ref(), memoryManager);
		mesh->addReference();
		return mesh.get();
	}
	
	CoroutineTask<IntrusivePointer<Material>> DxGraphics2DContext::makeSpriteMaterial() {
		IntrusivePointer<Material> material;
		auto shader = co_await resourceManager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(L"/shaders/DirectX/2d/sprite.xml"), DirectoryPath());
		if (shader != nullptr) {
			material = makeIntrusive<Material>();
			material->init(memoryManager);
			material->Shader = shader.get();
		}
		co_return material;
	}
	
	Mesh* DxGraphics2DContext::makeTileMapMesh(IntSize tileMapSize, Array<TileInfo>& tiles) {
		auto mesh = makeIntrusive<DxMesh>();
		auto tileMapMeshData = makeIntrusive<TileMapMeshData>();
		tileMapMeshData->init(tileMapSize, tiles);
		mesh->init(tileMapMeshData.ref(), memoryManager);
		mesh->addReference();
		return mesh.get();
	}
	
	CoroutineTask<IntrusivePointer<Material>> DxGraphics2DContext::makeTileMapMaterial() {
		IntrusivePointer<Material> material;
		auto shader = co_await resourceManager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(L"/shaders/DirectX/2d/sprite.xml"), DirectoryPath());
		if (shader != nullptr) {
			material = makeIntrusive<Material>();
			material->init(memoryManager);
			material->Shader = shader.get();
		}
		co_return material;
	}
}
