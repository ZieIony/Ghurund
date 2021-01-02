#pragma once

#include "ecs/Component.h"
#include "game/TransformComponent.h"
#include "game/parameter/ParameterProvider.h"
#include "graphics/mesh/Mesh.h"
#include "graphics/Material.h"
#include "graphics/RenderingStatistics.h"

#include <DirectXCollision.h>

namespace Ghurund {
	class DrawableComponent:public Component, public ParameterProvider {
	private:
		BoundingBox boundingBox;
		BoundingOrientedBox transformedBoundingBox;
		bool culled = false;
		bool selectable = true, visible = true, cullingEnabled = true;

		void finalize() {
			safeRelease(mesh);
			safeRelease(material);
		}

		static inline const auto& CONSTRUCTOR = NoArgsConstructor<DrawableComponent>();
		static const Ghurund::Type& GET_TYPE() {
			static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(DrawableComponent))
				.withConstructor(CONSTRUCTOR)
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

	protected:
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		List<Entity*> entities;

		virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
		virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

	public:

		~DrawableComponent() {
			finalize();
		}

		virtual void invalidate() override {
			finalize();
			__super::invalidate();
		}

		Mesh* getMesh() const {
			return mesh;
		}

		void setMesh(Mesh* mesh) {
			setPointer(this->mesh, mesh);
		}

		__declspec(property(get = getMesh, put = setMesh)) Mesh* Mesh;

		Material* getMaterial() {
			return material;
		}

		void setMaterial(Material* material) {
			setPointer(this->material, material);
		}

		__declspec(property(get = getMaterial, put = setMaterial)) Material* Material;

		virtual void initParameters(ParameterManager& parameterManager) override {
			material->initParameters(parameterManager);
		}

		virtual void updateParameters() override {
			material->updateParameters();
		}

		virtual const PointerArray<Parameter*>& getParameters() const override {
			return material->Parameters;
		}

		virtual bool isValid() const override {
			return material != nullptr && material->Valid && mesh != nullptr && mesh->Valid && __super::Valid;
		}

		void draw(Graphics& graphics, CommandList& commandList) {
			material->set(graphics, commandList);
			mesh->draw(commandList);
		}

		void draw(Graphics& graphics, CommandList& commandList, RenderingStatistics& statistics) {
			if (material->set(graphics, commandList))
				statistics.materialChanges++;
			mesh->draw(commandList);
			statistics.modelsRendered++;
			statistics.trianglesRendered += mesh->IndexCount / 3;
		}

		static const Array<ResourceFormat*>& getFormats() {
			static const Array<ResourceFormat*> formats = { (ResourceFormat*)& ResourceFormat::MODEL };
			return formats;
		}

		__declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;

		bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist) {
			return mesh->intersects(pos, dir, dist);
		}

		bool isCulled() {
			return culled;
		}

		__declspec(property(get = isCulled)) bool Culled;

		DirectX::BoundingBox* getBoundingBox() const {
			return &mesh->BoundingBox;
		}

		__declspec(property(get = getBoundingBox)) BoundingBox* BoundingBox;

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

		inline static const Ghurund::Type& TYPE = GET_TYPE();

		virtual const Ghurund::Type& getType() const override {
			return TYPE;
		}
	};
}