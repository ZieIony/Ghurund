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
		// resourceManager.Resources.remove(MESH_SPRITE);	// this resource is not present in resource cache
		safeRelease(MESH_SPRITE);
		resourceManager.Resources.remove(MATERIAL_SPRITE);
		safeRelease(MATERIAL_SPRITE);
		resourceManager.Resources.remove(MATERIAL_VISUALIZATION_BOX);
		safeRelease(MATERIAL_VISUALIZATION_BOX);
		resourceManager.Resources.remove(MATERIAL_VISUALIZATION_CAPSULE);
		safeRelease(MATERIAL_VISUALIZATION_CAPSULE);
		resourceManager.Resources.remove(MATERIAL_VISUALIZATION_SEGMENT);
		safeRelease(MATERIAL_VISUALIZATION_SEGMENT);
	}

	CoroutineTask<void> DxGraphics2DFeature::onInit() {
		co_await __super::onInit();
		
		auto mesh = makeIntrusive<DxMesh>();
		auto spriteMeshData = makeIntrusive<SpriteMeshData>();
		spriteMeshData->init();
		mesh->Data = spriteMeshData.get();
		mesh->init(memoryManager);
		MESH_SPRITE = mesh.get();
		MESH_SPRITE->addReference();
		
		auto materialSprite = co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/2d/sprite.xml"));
		MATERIAL_SPRITE = materialSprite.get();
		MATERIAL_SPRITE->addReference();
		auto materialBox = co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/2d/box.xml"));
		MATERIAL_VISUALIZATION_BOX = materialBox.get();
		MATERIAL_VISUALIZATION_BOX->addReference();
		auto materialCapsule = co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/2d/capsule.xml"));
		MATERIAL_VISUALIZATION_CAPSULE = materialCapsule.get();
		MATERIAL_VISUALIZATION_CAPSULE->addReference();
		auto materialSegment = co_await resourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/2d/segment.xml"));
		MATERIAL_VISUALIZATION_SEGMENT= materialSegment.get();
		MATERIAL_VISUALIZATION_SEGMENT->addReference();
	}

	void DxGraphics2DFeature::onDeinit() {
		uninitDxGraphicsFeature();
		__super::onDeinit();
	}
}
