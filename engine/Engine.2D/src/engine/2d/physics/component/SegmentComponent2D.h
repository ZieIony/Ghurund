#pragma once

#include "RigidBodyComponent2D.h"

#include <box2d.h>

namespace Ghurund::Engine::_2D {
	class SegmentComponent2D:public RigidBodyComponent2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SegmentComponent2D::GET_TYPE();
#pragma endregion

	private:
		b2ShapeId shapeId = {};
		float width = 1.0f;

		inline b2Segment makeSegment() {
			b2Segment segment;
			float w = fabs(scale.x * width) / 2;
			segment.point1 = { -w, 0 };
			segment.point2 = { w, 0 };
			return segment;
		}

		void uninitSegmentComponent2D();

	protected:
		virtual CoroutineTask<void> onInit() override;

		virtual void onUninit() {
			uninitSegmentComponent2D();
			__super::onUninit();
		};

	public:
		SegmentComponent2D(NotNull<Entity2D> owner):RigidBodyComponent2D(owner) {}
	
		~SegmentComponent2D() {
			if (IsInitialized)
				uninitSegmentComponent2D();
		}

		inline void updateShape() {
			b2Segment segment = makeSegment();
			b2Shape_SetSegment(shapeId, &segment);
		}

		inline float getWidth() const {
			return width;
		}

		inline void setWidth(float width) {
			this->width = width;
			updateShape();
		}

		__declspec(property(get = getWidth, put = setWidth)) float Width;

		virtual void update(const Timer& timer) override;
	};
}
