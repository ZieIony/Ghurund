#pragma once

#include "engine/3d/scene/component/Component3D.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine::_3D {
	class FullscreenQuadComponent:public Component3D {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;

		inline void setMesh(Mesh* mesh) {
			setPointer(this->mesh, mesh);
		}

		inline void uninitFullscreenQuadComponent() {
			safeRelease(mesh);
			safeRelease(material);
		}

	protected:
		Mesh* mesh = nullptr;
		Material* material = nullptr;

		[[nodiscard]]
		virtual CoroutineTask<void> onInit() override;

		virtual void onUninit() override {
			uninitFullscreenQuadComponent();
		}

	public:
		bool selectable = true, visible = true, cullingEnabled = true;

		FullscreenQuadComponent(NotNull<Entity3D> owner):Component3D(owner) {}

		virtual ~FullscreenQuadComponent() {
			if (IsInitialized)
				uninitFullscreenQuadComponent();
		}

		inline Mesh* getMesh() const {
			return mesh;
		}

		__declspec(property(get = getMesh, put = setMesh)) Mesh* Mesh;

		inline Material* getMaterial() {
			return material;
		}

		inline void setMaterial(Material* material) {
			setPointer(this->material, material);
		}

		__declspec(property(get = getMaterial, put = setMaterial)) Material* Material;

		virtual void queueDraw(RenderGroup& group) override;
	};
}
