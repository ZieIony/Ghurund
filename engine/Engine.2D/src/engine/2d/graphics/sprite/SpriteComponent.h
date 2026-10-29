#pragma once

#include "SpriteInputs.h"

#include "core/Colors.h"
#include "core/math/Size.h"
#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/texture/ITexture.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class SpriteComponent {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;
		bool selectable = true, visible = true, cullingEnabled = true;

	protected:
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		ITexture* colorTexture = nullptr;

	public:
		XMFLOAT2 offset = { 0, 0 };
		FloatSize size = { 1, 1 };
		Color tint = Colors::WHITE;
		float alpha = 1.0f;

	public:
		~SpriteComponent() {
			deinit();
		}

		CoroutineTask<void> init(ResourceManager& resourceManager);

		void deinit() {
			safeRelease(colorTexture);
			safeRelease(mesh);
			safeRelease(material);
		};

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

		inline ITexture* getColorTexture() const {
			return colorTexture;
		}

		inline void setColorTexture(ITexture* colorTexture) {
			setPointer(this->colorTexture, colorTexture);
		}

		__declspec(property(get = getColorTexture, put = setColorTexture)) ITexture* ColorTexture;

		/*bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist) {
			return mesh->intersects(pos, dir, dist);
		}

		bool isCulled() {
			return culled;
		}

		__declspec(property(get = isCulled)) bool Culled;

		::DirectX::BoundingBox* getBoundingBox() const {
			return &mesh->BoundingBox;
		}

		__declspec(property(get = getBoundingBox)) BoundingBox* BoundingBox;*/

		inline void setSelectable(bool selectable) {
			this->selectable = selectable;
		}

		inline bool isSelectable() const {
			return selectable;
		}

		__declspec(property(get = isSelectable, put = setSelectable)) bool Selectable;

		inline void setCullingEnabled(bool cullingEnabled) {
			this->cullingEnabled = cullingEnabled;
		}

		inline bool isCullingEnabled() const {
			return cullingEnabled;
		}

		__declspec(property(get = isCullingEnabled, put = setCullingEnabled)) bool CullingEnabled;

		inline void setVisible(bool visible) {
			this->visible = visible;
		}

		inline bool isVisible() const {
			return visible;
		}

		__declspec(property(get = isVisible, put = setVisible)) bool Visible;

		/*void update(const XMFLOAT4X4& transformation) {
			BoundingOrientedBox::CreateFromBoundingBox(transformedBoundingBox, boundingBox);
			transformedBoundingBox.Transform(transformedBoundingBox, XMLoadFloat4x4(&transformation));
		}*/

		void cull(BoundingFrustum& frustum) {
			culled = CullingEnabled && frustum.Contains(transformedBoundingBox) == ContainmentType::DISJOINT;
		}
	};
}
