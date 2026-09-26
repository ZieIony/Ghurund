#include "ghe2ddxpch.h"
#include "DxGraphics2DFeature.h"

#include "engine/graphics/material/Material.h"
#include "engine/directx/mesh/DxMesh.h"
#include "engine/graphics/mesh/SpriteMeshData.h"

namespace Ghurund::Engine::_2D::DirectX {
	using namespace Ghurund::Engine::DirectX;

    const Ghurund::Core::Type& DxGraphics2DFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxGraphics2DFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

	void DxGraphics2DFeature::uninitDxGraphicsFeature() {
		resourceManager.Resources.remove(MESH_SPRITE);
		resourceManager.Resources.remove(MATERIAL_SPRITE);
		resourceManager.Resources.remove(MATERIAL_VISUALIZATION_BOX);
		resourceManager.Resources.remove(MATERIAL_VISUALIZATION_CAPSULE);
		resourceManager.Resources.remove(MATERIAL_VISUALIZATION_SEGMENT);
	}

	CoroutineTask<void> DxGraphics2DFeature::onInit() {
		co_await __super::onInit();
		auto workingDir = DirectoryPath::getCurrentDirectory();
		
		auto mesh = makeIntrusive<DxMesh>();
		auto spriteMeshData = makeIntrusive<SpriteMeshData>();
		spriteMeshData->init();
		mesh->init(spriteMeshData.ref(), memoryManager);
		mesh->validate();
		mesh->Name = &MESH_SPRITE;
		resourceManager.Resources.put(mesh.get());
		
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/2d/sprite.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_SPRITE
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/2d/box.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_VISUALIZATION_BOX
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/2d/capsule.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_VISUALIZATION_CAPSULE
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/2d/segment.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_VISUALIZATION_SEGMENT
		);
	}

	void DxGraphics2DFeature::onUninit() {
		uninitDxGraphicsFeature();
		__super::onUninit();
	}
}
