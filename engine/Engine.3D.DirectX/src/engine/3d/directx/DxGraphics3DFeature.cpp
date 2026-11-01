#include "ghe3ddxpch.h"
#include "DxGraphics3DFeature.h"

#include "engine/directx/mesh/DxMesh.h"
#include "engine/graphics/material/Material.h"

namespace Ghurund::Engine::_3D::DirectX {
	using namespace Ghurund::Engine::DirectX;

    const Ghurund::Core::Type& DxGraphics3DFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxGraphics3DFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

	void DxGraphics3DFeature::uninitDxGraphics3DFeature() {
		resourceManager.Resources.remove(MESH_CUBE);
		safeRelease(MESH_CUBE);
		resourceManager.Resources.remove(MATERIAL_FORWARD_BASIC);
		safeRelease(MATERIAL_FORWARD_BASIC);
		resourceManager.Resources.remove(MATERIAL_FORWARD_LIT);
		safeRelease(MATERIAL_FORWARD_LIT);
		resourceManager.Resources.remove(MATERIAL_FORWARD_NORMALS);
		safeRelease(MATERIAL_FORWARD_NORMALS);
		resourceManager.Resources.remove(MATERIAL_FORWARD_TANGENTS);
		safeRelease(MATERIAL_FORWARD_TANGENTS);
		resourceManager.Resources.remove(MATERIAL_FORWARD_TEXCOORDS);
		safeRelease(MATERIAL_FORWARD_TEXCOORDS);
	}

	CoroutineTask<void> DxGraphics3DFeature::onInit() {
		co_await __super::onInit();
		auto workingDir = DirectoryPath::getCurrentDirectory();

		auto cubeMesh = co_await resourceManager.load<DxMesh>(
			ResourceManager::makeEngineResourcePath(L"models/cube.fbx"),
			workingDir, ResourceFormat::AUTO, { .targetState = ResourceState::EMPTY }
		);
		MESH_CUBE = cubeMesh.get();
		MESH_CUBE->addReference();
		auto basicMaterial = co_await resourceManager.load<Material>(
			ResourceManager::makeEngineResourcePath(L"materials/DirectX/3d/forward/basic.xml"),
			workingDir, ResourceFormat::AUTO, { .targetState = ResourceState::EMPTY }
		);
		MATERIAL_FORWARD_BASIC = basicMaterial.get();
		MATERIAL_FORWARD_BASIC->addReference();
		auto basicLitMaterial = co_await resourceManager.load<Material>(
			ResourceManager::makeEngineResourcePath(L"materials/DirectX/3d/forward/basicLit.xml"),
			workingDir, ResourceFormat::AUTO, { .targetState = ResourceState::EMPTY }
		);
		MATERIAL_FORWARD_LIT = basicLitMaterial.get();
		MATERIAL_FORWARD_LIT->addReference();
		auto normalsMaterial = co_await resourceManager.load<Material>(
			ResourceManager::makeEngineResourcePath(L"materials/DirectX/3d/forward/normals.xml"),
			workingDir, ResourceFormat::AUTO, { .targetState = ResourceState::EMPTY }
		);
		MATERIAL_FORWARD_NORMALS = normalsMaterial.get();
		MATERIAL_FORWARD_NORMALS->addReference();
		auto tangentsMaterial = co_await resourceManager.load<Material>(
			ResourceManager::makeEngineResourcePath(L"materials/DirectX/3d/forward/tangents.xml"),
			workingDir, ResourceFormat::AUTO, { .targetState = ResourceState::EMPTY }
		);
		MATERIAL_FORWARD_TANGENTS = tangentsMaterial.get();
		MATERIAL_FORWARD_TANGENTS->addReference();
		auto texCoordsMaterial = co_await resourceManager.load<Material>(
			ResourceManager::makeEngineResourcePath(L"materials/DirectX/3d/forward/texCoords.xml"),
			workingDir, ResourceFormat::AUTO, { .targetState = ResourceState::EMPTY }
		);
		MATERIAL_FORWARD_TEXCOORDS = texCoordsMaterial.get();
		MATERIAL_FORWARD_TEXCOORDS->addReference();
	}

	void DxGraphics3DFeature::onDeinit() {
		uninitDxGraphics3DFeature();
	}
}
