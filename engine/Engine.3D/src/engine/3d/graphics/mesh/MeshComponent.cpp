#include "ghe3dpch.h"
#include "MeshComponent.h"

#include "engine/3d/Graphics3DFeature.h"

namespace Ghurund::Engine::_3D {
	CoroutineTask<void> MeshComponent::init(IGPUMemoryManager& memoryManager) {
		if (!Mesh)
			Mesh = Graphics3DFeature::MESH_CUBE;
		if (!Material) {
			auto basicMaterial = IntrusivePointer((Ghurund::Engine::Material*)Graphics3DFeature::MATERIAL_FORWARD_LIT->clone());
			basicMaterial->init(memoryManager);
			Material = basicMaterial.get();
		}
		co_return;
	}
}
