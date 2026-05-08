#pragma once

#include "Component2D.h"
#include "VisualizationInputs.h"

#include "core/Colors.h"
#include "core/math/Matrix.h"

namespace Ghurund::Engine::_2D {
	class VisualizationComponent2D:public Component2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = VisualizationComponent2D::GET_TYPE();
#pragma endregion

	private:
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		Color color = [] {
			while (true) {
				Color c = Colors::VALUES[random(0ull, Colors::VALUES.Size)].toLinear();
				if (c.Brightness > 0.5f)
					return c;
			}
		}();
		VisualizationInputs inputs;
		XMFLOAT4X4 worldTransformation = Ghurund::Core::makeIdentityMatrix();
		XMFLOAT2 extents = { 0, 0 };

	public:
		VisualizationComponent2D(NotNull<Entity2D> owner, World2D& world):Component2D(owner, world) {}

		~VisualizationComponent2D();

		inline void setMesh(Mesh* mesh) {
			setPointer(this->mesh, mesh);
		}

		__declspec(property(put = setMesh)) Mesh* Mesh;

		inline void setMaterial(Material* material) {
			setPointer(this->material, material);
			if (material) {
				inputs.init(material->Inputs);
				inputs.Color = color;
			}
		}

		__declspec(property(put = setMaterial)) Material* Material;

		inline void setTransformation(const XMFLOAT4X4& transformation) {
			this->worldTransformation = transformation;
		}

		__declspec(property(put = setTransformation)) const XMFLOAT4X4& Transformation;

		inline void setExtents(const XMFLOAT2& extents) {
			this->extents = extents;
		}

		__declspec(property(put = setExtents)) const XMFLOAT2& Extents;

		virtual void draw(RenderGroup& group) override;
	};
}