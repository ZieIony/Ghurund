#pragma once

#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine::_3D {
	class MeshComponent {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;

		uint32_t id;
		Mesh* mesh = nullptr;
		Material* material = nullptr;

	public:
		bool selectable = true, visible = true, cullingEnabled = true;

		virtual ~MeshComponent() {
			deinit();
		}

		[[nodiscard]]
		void init(uint32_t id);

		inline void deinit() {
			safeRelease(mesh);
			safeRelease(material);
		}

		inline uint32_t getId() const {
			return id;
		}

		__declspec(property(get = getId)) uint32_t Id;

		Mesh* getMesh() const {
			return mesh;
		}

		void setMesh(Mesh* mesh) {
			setPointer(this->mesh, mesh);
		}

		__declspec(property(get = getMesh, put = setMesh)) Mesh* Mesh;

		Material* getMaterial() {
			return material;
		}

		void setMaterial(Material* material) {
			setPointer(this->material, material);
		}

		__declspec(property(get = getMaterial, put = setMaterial)) Material* Material;
	};
}
