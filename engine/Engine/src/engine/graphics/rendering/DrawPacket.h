#pragma once

#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class DrawPacket {
	private:
		Mesh* mesh;
		Material* material;
		float order;

	public:
		DrawPacket(
			NotNull<Mesh> mesh,
			NotNull<Material> material,
			float order
		):mesh(mesh.get()), material(material.get()), order(order) {
			mesh->addReference();
			material->addReference();
		}

		DrawPacket(const DrawPacket& other):mesh(other.mesh), material(other.material), order(order) {
			mesh->addReference();
			material->addReference();
		}

		DrawPacket(DrawPacket&& other):mesh(other.mesh), material(other.material), order(order) {
			other.mesh = nullptr;
			other.material = nullptr;
		}

		~DrawPacket() {
			if (mesh)
				mesh->release();
			if (material)
				material->release();
		}

		inline Mesh* getMesh() const {
			return mesh;
		}

		__declspec(property(get = getMesh)) Mesh* Mesh;

		inline Material* getMaterial() const {
			return material;
		}

		__declspec(property(get = getMaterial)) Material* Material;

		inline float getOrder() const {
			return order;
		}

		__declspec(property(get = getOrder)) float Order;

		inline DrawPacket& operator=(const DrawPacket& other) {
			if (this == &other)
				return *this;
			mesh = other.mesh;
			mesh->addReference();
			material = other.material;
			material->addReference();
			order = other.order;
			return *this;
		}

		inline DrawPacket& operator=(DrawPacket&& other) {
			if (this == &other)
				return *this;
			mesh = other.mesh;
			other.mesh = nullptr;
			material = other.material;
			other.material = nullptr;
			order = other.order;
			return *this;
		}
	};
}