#pragma once

#include "SpriteInputs.h"

#include "core/Colors.h"
#include "core/math/Size.h"
#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/texture/ITexture.h"
#include "engine/2d/graphics/transform/TransformComponent2D.h"
#include "engine/graphics/rendering/ObjectParameters.h"
#include "engine/2d/Graphics2DFeature.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class SpriteComponent {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;

		uint32_t id;
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
		bool selectable = true, visible = true, cullingEnabled = true;

		~SpriteComponent() {
			deinit();
		}

		inline void init(uint32_t id) {
			this->id = id;
			Mesh = Graphics2DFeature::MESH_SPRITE;
			Material = Graphics2DFeature::MATERIAL_SPRITE;
		}

		inline void deinit() {
			safeRelease(colorTexture);
			safeRelease(mesh);
			safeRelease(material);
		};

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
			if (material) {
				inputs.init(material->getShader(MaterialVariantType::UNLIT)->Inputs);
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

		inline void update(const TransformComponent2D& transform, ObjectParameters& parameters) {
			auto w = XMMatrixTranslation(offset.x, offset.y, 0) *
				XMMatrixScaling(size.Width, size.Height, 1) *
				XMLoadFloat4x4(&transform.WorldTransformation);
			XMFLOAT4X4 world;
			XMStoreFloat4x4(&world, XMMatrixTranspose(w));

			parameters.world = world;

			auto bw = XMMatrixTranslation(offset.x, offset.y, 0) *
				XMMatrixScaling(abs(size.Width), abs(size.Height), 1) *
				XMLoadFloat4x4(&transform.WorldTransformation);
			XMFLOAT4X4 boxWorld;
			XMStoreFloat4x4(&boxWorld, XMMatrixTranspose(bw));
			BoundingOrientedBox::CreateFromBoundingBox(transformedBoundingBox, boundingBox);
			transformedBoundingBox.Transform(transformedBoundingBox, bw);
		}

		inline void cull(const BoundingOrientedBox& viewBox) {
			culled = cullingEnabled && viewBox.Contains(transformedBoundingBox) == ContainmentType::DISJOINT;
		}
	};
}
