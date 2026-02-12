#pragma once

#include "BodyComponent2D.h"
#include <engine/graphics/mesh/Mesh.h>
#include <engine/graphics/material/Material.h>
#include <engine/2d/physics/World2D.h>

#include <box2d.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class BoxComponent2D:public BodyComponent2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = BoxComponent2D::GET_TYPE();
#pragma endregion

	private:
		b2ShapeId shapeId;

	protected:
		virtual void updateSize() override;

	public:
		BoxComponent2D() {}

		BoxComponent2D(NotNull<Mesh> mesh, NotNull<Material> material):BodyComponent2D(mesh, material) {}

		void init(const World2D& world);

		//inline void setMass(float massKg) {
		//	b2Shape_SetDensity()
		//}
	};
}