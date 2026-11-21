#include "ghe3dpch.h"
#include "MeshComponent.h"

#include "engine/3d/Graphics3DFeature.h"

namespace Ghurund::Engine::_3D {
	void MeshComponent::init(uint32_t id) {
		this->id = id;
		if (!Mesh)
			Mesh = Graphics3DFeature::MESH_CUBE;
		if (!Material)
			Material = Graphics3DFeature::MATERIAL_FORWARD_LIT;
	}
}
