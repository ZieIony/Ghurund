#pragma once

#include "BodyComponent2D.h"

#include "engine/2d/scene/component/TransformComponent2D.h"

#include <box2d.h>

namespace Ghurund::Engine::_2D {
	class SegmentComponent2D:public BodyComponent2D {
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
		b2ShapeId shapeId;
		float width = 1.0f;

		EventHandler<TransformComponent2D> scaleChangedHandler = [&](TransformComponent2D& transform) -> bool {
			updateShape();
			return true;
		};

		inline b2Segment makeSegment() {
			b2Segment segment;
			float w = fabs(scale.x * width) / 2;
			segment.point1 = { -w, 0 };
			segment.point2 = { w, 0 };
			return segment;
		}

		inline void updateShape() {
			b2Segment segment = makeSegment();
			b2Shape_SetSegment(shapeId, &segment);
		}

		void uninitSegmentComponent2D();

	protected:
		virtual CoroutineTask<void> onInit() override;

		virtual void onUninit() {
			uninitSegmentComponent2D();
			__super::onUninit();
		};

	public:
		SegmentComponent2D(NotNull<Entity2D> owner, World2D& world):BodyComponent2D(owner, world) {}
	
		~SegmentComponent2D() {
			if (IsInitialized)
				uninitSegmentComponent2D();
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
