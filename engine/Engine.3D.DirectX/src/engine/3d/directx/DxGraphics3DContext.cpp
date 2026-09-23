#include "ghe3ddxpch.h"
#include "DxGraphics3DContext.h"

#include "engine/directx/mesh/DxMesh.h"
#include "engine/graphics/mesh/QuadMeshData.h"

namespace Ghurund::Engine::_3D::DirectX {
	CoroutineTask<IntrusivePointer<Mesh>> DxGraphics3DContext::makeQuadMesh() {
		auto mesh = makeIntrusive<DxMesh>();
		auto meshData = ghnew QuadMeshData();
		meshData->init();
		mesh->init(*meshData, memoryManager);
		meshData->release();
		co_return mesh;
	}
}
