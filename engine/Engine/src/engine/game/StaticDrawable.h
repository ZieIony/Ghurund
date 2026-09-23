#pragma once

#include "core/object/AsyncInitializable.h"
#include "core/math/Size.h"
#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/rendering/RenderGroup.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class StaticDrawable:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = StaticDrawable::GET_TYPE();
#pragma endregion

	private:
		bool visible = true;
		XMFLOAT2 offset;
		FloatSize size = { 1, 1 };
		MatrixInput* worldInput;

	protected:
		float drawOrder = 0;
		Mesh* mesh = nullptr;
		Material* material = nullptr;

	public:
		~StaticDrawable() {
			if (mesh)
				mesh->release();
			if (material)
				material->release();
		}

		inline void setMesh(Mesh* mesh) {
			setPointer(this->mesh, mesh);
		}

		__declspec(property(put = setMesh)) Mesh* Mesh;

		inline void setMaterial(Material* material) {
			setPointer(this->material, material);
			if (material)
				worldInput = (MatrixInput*)material->Inputs.get(MatrixInput::INPUT_NAME_WORLD);
		}

		__declspec(property(put = setMaterial)) Material* Material;

		inline const XMFLOAT2& getOffset() const {
			return offset;
		}

		inline void setOffset(float x, float y) {
			offset.x = x;
			offset.y = y;
		}

		inline void setOffset(const XMFLOAT2& offset) {
			this->offset.x = offset.x;
			this->offset.y = offset.y;
		}

		__declspec(property(get = getOffset, put = setOffset)) const XMFLOAT2& Offset;

		inline const FloatSize& getSize() const {
			return size;
		}

		inline void setSize(const FloatSize& size) {
			this->size = size;
		}

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;

		void queueDraw(RenderGroup& group);

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
	};
}
