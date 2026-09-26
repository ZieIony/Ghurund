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
		resourceManager.Resources.remove(MATERIAL_FORWARD_BASIC);
		resourceManager.Resources.remove(MATERIAL_FORWARD_LIT);
		resourceManager.Resources.remove(MATERIAL_FORWARD_NORMALS);
		resourceManager.Resources.remove(MATERIAL_FORWARD_TANGENTS);
		resourceManager.Resources.remove(MATERIAL_FORWARD_TEXCOORDS);
	}

	CoroutineTask<void> DxGraphics3DFeature::onInit() {
		co_await __super::onInit();
		auto workingDir = DirectoryPath::getCurrentDirectory();

		co_await resourceManager.load<DxMesh>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"models/cube.fbx"),
			workingDir, ResourceFormat::AUTO, &MESH_CUBE
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forward/basic.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_FORWARD_BASIC
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forward/basicLit.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_FORWARD_LIT
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forward/normals.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_FORWARD_NORMALS
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forward/tangents.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_FORWARD_TANGENTS
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forward/texCoords.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_FORWARD_TEXCOORDS
		);
	}

	void DxGraphics3DFeature::onUninit() {
		uninitDxGraphics3DFeature();
	}
}
