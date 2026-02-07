#pragma once

#include "SpriteAnimation.h"
#include "SpriteInputs.h"

#include "engine/2d/entity/Transform2DComponent.h"
#include "core/Colors.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine::_2D {
	class AnimatedSpriteComponent:public Transform2DComponent {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;
		bool selectable = true, visible = true, cullingEnabled = true;

		XMFLOAT2 size = { 0, 0 };

		void finalize() {
			safeRelease(mesh);
			safeRelease(material);
		}

	protected:
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		Color tint = Colors::WHITE;
		float alpha = 1.0f;
		SpriteAnimation animation;
		SpriteInputs inputs;

	public:
		AnimatedSpriteComponent() {}

		AnimatedSpriteComponent(NotNull<Mesh> mesh, NotNull<Material> material):mesh(mesh.get()), material(material.get()) {
			mesh->addReference();
			material->addReference();
			inputs.init(material->Inputs);
		}

		virtual ~AnimatedSpriteComponent() {
			finalize();
		}

		virtual void invalidate() {
			finalize();
		}

		inline const XMFLOAT2& getSize() const {
			return size;
		}

		inline void setSize(const XMFLOAT2& size) {
			this->size = size;
		}

		__declspec(property(get = getSize, put = setSize)) const XMFLOAT2& Size;

		inline void setMesh(Mesh* mesh) {
			setPointer(this->mesh, mesh);
		}

		__declspec(property(put = setMesh)) Mesh* Mesh;

		inline void setMaterial(Material* material) {
			setPointer(this->material, material);
			if (material)
				inputs.init(material->Inputs);
		}

		__declspec(property(put = setMaterial)) Material* Material;

		inline void setTint(const Color& color) {
			this->tint = color;
		}

		__declspec(property(put = setTint)) const Color& Tint;

		inline void setAlpha(float alpha) {
			this->alpha = alpha;
		}

		__declspec(property(put = setAlpha)) float Alpha;

		inline SpriteAnimation& getAnimation() {
			return animation;
		}

		__declspec(property(get = getAnimation)) SpriteAnimation& Animation;

		virtual bool isValid() const {
			return material != nullptr && material->Valid && mesh != nullptr && mesh->Valid;
		}

		virtual void update(uint64_t time) override {
			__super::update(time);
			animation.update(time);
		}

		virtual void draw(RenderGroup& group, const XMFLOAT4X4& parentTransformation) override;

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

		void update(const XMFLOAT4X4& transformation) {
			BoundingOrientedBox::CreateFromBoundingBox(transformedBoundingBox, boundingBox);
			transformedBoundingBox.Transform(transformedBoundingBox, XMLoadFloat4x4(&transformation));
		}

		void cull(BoundingFrustum& frustum) {
			culled = CullingEnabled && frustum.Contains(transformedBoundingBox) == ContainmentType::DISJOINT;
		}
	};
}