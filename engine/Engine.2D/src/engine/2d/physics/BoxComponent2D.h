#pragma once

#include "BodyComponent2D.h"

#include <box2d.h>
#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class BoxComponent2D:public BodyComponent2D {
	private:
		bool hasShape = false;
		b2ShapeId shapeId;
		FloatSize size = { 1, 1 };

	public:
		BoxComponent2D() {}

		BoxComponent2D(NotNull<Mesh> mesh, NotNull<Material> material):BodyComponent2D(mesh, material) {}

		inline void init(const World2D& world) {
			__super::init(world);

			b2Polygon box = b2MakeBox(size.Width / 2, size.Height / 2);
			b2ShapeDef shapeDef = b2DefaultShapeDef();
			shapeId = b2CreatePolygonShape(Id, &shapeDef, &box);
		}

		virtual void setSize(const FloatSize& size) override {
			this->size = size;
			b2Polygon box = b2MakeBox(size.Width / 2, size.Height / 2);
			b2Shape_SetPolygon(shapeId, &box);
		}

		virtual const FloatSize& getSize() const override {
			return size;
		}

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;

		//inline void setMass(float massKg) {
		//	b2Shape_SetDensity()
		//}
	};
}