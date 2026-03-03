#include "ghe2ddxpch.h"
#include "DxGraphics2DContext.h"

namespace Ghurund::Engine::_2D::DirectX {
	Mesh* DxGraphics2DContext::makeSpriteMesh() {
		auto mesh = makeIntrusive<DxMesh>();
		mesh->init(spriteMeshData.ref(), memoryManager);
		mesh->addReference();
		return mesh.get();
	}
	
	Material* DxGraphics2DContext::makeSpriteMaterial() {
		Material* material = nullptr;
		auto shader = IntrusivePointer<Shader>(resourceManager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(L"/shaders/DirectX/2d/sprite.xml"), DirectoryPath()));
		if (shader != nullptr) {
			material = ghnew Material(memoryManager);
			material->Shader = shader.get();
		}
		return material;
	}
	
	Mesh* DxGraphics2DContext::makeTileMapMesh(IntSize tileMapSize, Array<TileInfo>& tiles) {
		auto mesh = makeIntrusive<DxMesh>();
		auto tileMapMeshData = makeIntrusive<TileMapMeshData>();
		tileMapMeshData->init(tileMapSize, tiles);
		mesh->init(tileMapMeshData.ref(), memoryManager);
		mesh->addReference();
		return mesh.get();
	}
	
	Material* DxGraphics2DContext::makeTileMapMaterial() {
		Material* material = nullptr;
		auto shader = IntrusivePointer<Shader>(resourceManager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(L"/shaders/DirectX/2d/sprite.xml"), DirectoryPath()));
		if (shader != nullptr) {
			material = ghnew Material(memoryManager);
			material->Shader = shader.get();
		}
		return material;
	}
}
