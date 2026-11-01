#pragma once

#include "MeshInputs.h"
#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine::_3D {
	class MeshComponent {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;

	protected:
		Mesh* mesh = nullptr;
		Material* material = nullptr;

	public:
		bool selectable = true, visible = true, cullingEnabled = true;

		virtual ~MeshComponent() {
			deinit();
		}

		[[nodiscard]]
		CoroutineTask<void> init(IGPUMemoryManager& memoryManager);

		inline void deinit() {
			safeRelease(mesh);
			safeRelease(material);
		}

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
