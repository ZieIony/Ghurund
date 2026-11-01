#pragma once

#include "SpriteInputs.h"

#include "core/Colors.h"
#include "core/math/Size.h"
#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/texture/ITexture.h"
#include <engine/2d/scene/transform/TransformComponent2D.h>

#include <DirectXCollision.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class SpriteComponent {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;
		bool selectable = true, visible = true, cullingEnabled = true;

		Mesh* mesh = nullptr;
		Material* material = nullptr;
		SpriteInputs inputs;
		ITexture* colorTexture = nullptr;
		Color tint = Colors::WHITE;
		float alpha = 1.0f;

	public:
		XMFLOAT2 offset = { 0, 0 };
		FloatSize size = { 1, 1 };

	public:
		~SpriteComponent() {
			deinit();
		}

		void init(IGPUMemoryManager& memoryManager);

		inline void deinit() {
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
			if (material) {
				inputs.init(material->Inputs);
				inputs.ColorTexture = colorTexture;
				inputs.Tint = tint;
				inputs.Alpha = alpha;
			}
		}

		__declspec(property(get = getMaterial, put = setMaterial)) Material* Material;

		inline ITexture* getColorTexture() const {
			return colorTexture;
		}

		inline void setColorTexture(ITexture* colorTexture) {
			setPointer(this->colorTexture, colorTexture);
			if (material)
				inputs.ColorTexture = colorTexture;
		}

		__declspec(property(get = getColorTexture, put = setColorTexture)) ITexture* ColorTexture;

		inline const Color& getTint() const {
			return tint;
		}

		inline void setTint(const Color& color) {
			this->tint = color;
			if (material)
				inputs.Tint = tint;
		}

		__declspec(property(get = getTint, put = setTint)) const Color& Tint;

		inline float getAlpha() const {
			return alpha;
		}

		inline void setAlpha(float alpha) {
			this->alpha = alpha;
			if (material)
				inputs.Alpha = alpha;
		}

		__declspec(property(get = getAlpha, put = setAlpha)) float Alpha;

		/*bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist) {
			return mesh->intersects(pos, dir, dist);
		}*/

		inline bool getIsCulled() const {
			return culled;
		}

		__declspec(property(get = getIsCulled)) bool IsCulled;

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

		inline void update(const TransformComponent2D& transform) {
			auto w = XMMatrixTranslation(offset.x, offset.y, 0) *
				XMMatrixScaling(size.Width, size.Height, 1) *
				XMLoadFloat4x4(&transform.WorldTransformation);
			XMFLOAT4X4 world;
			XMStoreFloat4x4(&world, XMMatrixTranspose(w));

			inputs.Transformation = world;

			BoundingOrientedBox::CreateFromBoundingBox(transformedBoundingBox, boundingBox);
			transformedBoundingBox.Transform(transformedBoundingBox, w);
		}

		inline void cull(const BoundingOrientedBox& viewBox) {
			culled = CullingEnabled && viewBox.Contains(transformedBoundingBox) == ContainmentType::DISJOINT;
		}
	};
}
