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
	}

	CoroutineTask<void> DxGraphics3DFeature::onInit() {
		co_await __super::onInit();
		auto workingDir = DirectoryPath::getCurrentDirectory();

		co_await resourceManager.load<DxMesh>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"models/cube.fbx"),
			workingDir, ResourceFormat::AUTO, &MESH_CUBE
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forwardBasic.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_FORWARD_BASIC
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forwardLit.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_FORWARD_LIT
		);
		co_await resourceManager.load<Material>(
			ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forwardNormals.xml"),
			workingDir, ResourceFormat::AUTO, &MATERIAL_FORWARD_NORMALS
		);
	}

	void DxGraphics3DFeature::onUninit() {
		uninitDxGraphics3DFeature();
	}
}
