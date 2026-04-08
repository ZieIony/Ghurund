#pragma once

#include "SpriteInputs.h"

#include "core/Colors.h"
#include "core/math/Size.h"
#include "engine/2d/scene/component/TransformComponent2D.h"
#include "engine/2d/scene/Entity2D.h"
#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class BaseSpriteComponent:public TransformComponent2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = BaseSpriteComponent::GET_TYPE();
#pragma endregion

	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;
		bool selectable = true, visible = true, cullingEnabled = true;
		FloatSize size = { 1, 1 };

		inline void uninitBaseSpriteComponent() {
			safeRelease(mesh);
			safeRelease(material);
		};

	protected:
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		Color tint = Colors::WHITE;
		float alpha = 1.0f;
		SpriteInputs inputs;

		virtual CoroutineTask<void> onInit() override {
			co_await __super::onInit();
			Mesh = IntrusivePointer(Owner->Context->makeSpriteMesh()).get();
			Material = (co_await Owner->Context->makeSpriteMaterial()).get();
		}

		virtual void onUninit() {
			uninitBaseSpriteComponent();
			__super::onUninit();
		};

	public:
		virtual ~BaseSpriteComponent() = 0 {
			if (IsInitialized)
				uninitBaseSpriteComponent();
		}

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

		inline void setSize(const FloatSize& size) {
			this->size = size;
		}

		inline const FloatSize& getSize() const {
			return size;
		}

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;

		virtual void draw(RenderGroup& group) override;

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