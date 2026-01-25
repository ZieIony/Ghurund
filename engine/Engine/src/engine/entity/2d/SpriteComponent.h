#pragma once

#include "SpriteInputs.h"
#include "Transform2DComponent.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine {
	class SpriteComponent:public Transform2DComponent {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;
		bool selectable = true, visible = true, cullingEnabled = true;

		FloatSize size = { 0, 0 };

		void finalize() {
			safeRelease(mesh);
			safeRelease(material);
			safeRelease(colorTexture);
		}

	protected:
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		ITexture* colorTexture = nullptr;
		SpriteInputs inputs;

	public:
		SpriteComponent() {}

		SpriteComponent(NotNull<Mesh> mesh, NotNull<Material> material):mesh(mesh.get()), material(material.get()) {
			mesh->addReference();
			material->addReference();
			inputs.init(material->Inputs);
		}

		virtual ~SpriteComponent() {
			finalize();
		}

		virtual void invalidate() {
			finalize();
		}

		inline const FloatSize& getSize() const {
			return size;
		}

		inline void setSize(const FloatSize& size) {
			this->size = size;
		}

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;

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

		inline void setColorTexture(ITexture* colorTexture) {
			setPointer(this->colorTexture, colorTexture);
		}

		__declspec(property(put = setColorTexture)) ITexture* ColorTexture;

		virtual bool isValid() const {
			return material != nullptr && material->Valid && mesh != nullptr && mesh->Valid;
		}

		virtual void draw(RenderGroup& group, const XMFLOAT2& parentPosition) override {
			if (!mesh || !material)
				return;
			mesh->addReference();
			material->addReference();
			inputs.Position = parentPosition + Position;
			inputs.Size = { size.Width, size.Height };
			inputs.ColorTexture = colorTexture;
			group.objects.add(DrawPacket{
				IntrusivePointer<Ghurund::Engine::Mesh>(mesh),
				IntrusivePointer<Ghurund::Engine::Material>(material),
				XMFLOAT3(parentPosition.x + Position.x, parentPosition.y + Position.y, 0)
			});
		}

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

		void update(const XMFLOAT4X4 &transformation) {
			BoundingOrientedBox::CreateFromBoundingBox(transformedBoundingBox, boundingBox);
			transformedBoundingBox.Transform(transformedBoundingBox, XMLoadFloat4x4(&transformation));
		}

		void cull(BoundingFrustum& frustum) {
			culled = CullingEnabled && frustum.Contains(transformedBoundingBox) == ContainmentType::DISJOINT;
		}
	};
}