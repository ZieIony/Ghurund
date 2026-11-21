#pragma once

#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class DrawPacket {
	public:
		const uint32_t id;
		const Mesh* mesh;
		const Material* material;

		DrawPacket(
			uint32_t id,
			NotNull<Mesh> mesh,
			NotNull<Material> material
		):id(id), mesh(mesh.get()), material(material.get()) {
			mesh->addReference();
			material->addReference();
		}

		DrawPacket(const DrawPacket& other):id(other.id), mesh(other.mesh), material(other.material) {
			mesh->addReference();
			material->addReference();
		}

		DrawPacket(DrawPacket&& other) noexcept:id(other.id), mesh(other.mesh), material(other.material) {
			other.mesh = nullptr;
			other.material = nullptr;
		}

		~DrawPacket() {
			if (mesh)
				mesh->release();
			if (material)
				material->release();
		}
	};
}
