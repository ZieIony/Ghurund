#pragma once

#include "core/Colors.h"
#include "core/math/Matrix.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/material/Material.h"
#include <engine/2d/scene/transform/TransformComponent2D.h>
#include <engine/2d/physics/RigidBodyComponent2D.h>

namespace Ghurund::Engine::_2D {
	class VisualizationComponent2D {
	private:
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		XMFLOAT4X4 worldTransformation = Ghurund::Core::makeIdentityMatrix();

	public:
		Color color = [] {
			while (true) {
				Color c = Colors::VALUES[random(0ull, Colors::VALUES.Size)].toLinear();
				if (c.Brightness > 0.5f)
					return c;
			}
		}();
		XMFLOAT2 extents = { 0, 0 };

		~VisualizationComponent2D();

		void init(IGPUMemoryManager& memoryManager, const RigidBodyComponent2D& rigidBody);

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

		inline const XMFLOAT4X4& getTransformation() const {
			return worldTransformation;
		}

		inline void setTransformation(const XMFLOAT4X4& transformation) {
			this->worldTransformation = transformation;
		}

		__declspec(property(get = getTransformation, put = setTransformation)) const XMFLOAT4X4& Transformation;

		void update(const RigidBodyComponent2D& rigidBody);
	};
}