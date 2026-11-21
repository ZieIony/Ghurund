#pragma once

#include "core/Colors.h"
#include "core/math/Matrix.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/material/Material.h"
#include "engine/2d/physics/RigidBodyComponent2D.h"

namespace Ghurund::Engine::_2D {
	class VisualizationComponent2D {
	private:
		uint32_t id;
		Mesh* mesh = nullptr;
		Material* material = nullptr;

	public:
		Color color = [] {
			while (true) {
				Color c = Colors::VALUES[random(0ull, Colors::VALUES.Size)].toLinear();
				if (c.Brightness > 0.5f)
					return c;
			}
		}();
		XMFLOAT2 extents = { 0, 0 };
		XMFLOAT4X4 worldTransformation = Ghurund::Core::makeIdentityMatrix();

		~VisualizationComponent2D();

		void init(uint32_t id, const RigidBodyComponent2D& rigidBody);

		inline uint32_t getId() const {
			return id;
		}

		__declspec(property(get = getId)) uint32_t Id;

		inline Mesh* getMesh() const {
			return mesh;
		}

		inline void setMesh(Mesh* mesh) {
			setPointer(this->mesh, mesh);
		}

		__declspec(property(get = getMesh, put = setMesh)) Mesh* Mesh;

		inline Material* getMaterial() const {
			return material;
		}

		inline void setMaterial(Material* material) {
			setPointer(this->material, material);
		}

		__declspec(property(get = getMaterial, put = setMaterial)) Material* Material;

		void update(const RigidBodyComponent2D& rigidBody);
	};
}
