#pragma once

#include "BodyComponent2D.h"

#include <box2d.h>
#include <DirectXMath.h>

namespace Ghurund::Engine::_2D {
	using namespace ::DirectX;

	class SegmentComponent2D:public BodyComponent2D {
	private:
		bool hasShape = false;
		b2ShapeId shapeId;
		FloatSize size = { 1, 1 };
		float rotation = 0;

	public:
		SegmentComponent2D() {}

		SegmentComponent2D(NotNull<Mesh> mesh, NotNull<Material> material):BodyComponent2D(mesh, material) {}

		inline void init(const World2D& world) {
			__super::init(world);

			b2Segment segment;
			segment.point1 = { -10, 0 };
			segment.point2 = { 10, 0 };
			size = { 20, 1 };
			b2ShapeDef shapeDef = b2DefaultShapeDef();
			shapeId = b2CreateSegmentShape(Id, &shapeDef, &segment);
		}

		inline void setPoints(const XMFLOAT2& p1, const XMFLOAT2& p2) {
			XMFLOAT2 l;
			XMStoreFloat2(&l, XMVector2Length(XMLoadFloat2(&p1) - XMLoadFloat2(&p2)));
			this->size = { l.x, 1.0f };
			this->rotation = std::atan2f(p1.y - p2.y, p1.x - p2.x);
			b2Segment segment;
			segment.point1 = { p1.x, p1.y };
			segment.point2 = { p2.x, p2.y };
			b2Shape_SetSegment(shapeId, &segment);
		}

		virtual void setSize(const FloatSize& size) override {
			if (this->size.Width != size.Width) {
				b2Segment segment = b2Shape_GetSegment(shapeId);
				XMFLOAT2 center = { (segment.point1.x + segment.point2.x) / 2, (segment.point1.y + segment.point2.y) / 2 };
				segment.point1 = { (segment.point1.x - center.x) / size.Width * 2 + center.x, (segment.point1.y - center.y) / size.Height * 2 + center.y };
				segment.point2 = { (segment.point2.x - center.x) / size.Width * 2 + center.x, (segment.point2.y - center.y) / size.Height * 2 + center.y };
				this->size.Width = size.Width;
				b2Shape_SetSegment(shapeId, &segment);
			}
		}

		virtual const FloatSize& getSize() const override {
			return size;
		}

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;
	};
}