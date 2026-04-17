#pragma once

#include "BodyComponent2D.h"

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

		inline void uninitSegmentComponent2D() {
			if (visualizationComponent) {
				Components.remove(visualizationComponent);
				visualizationComponent->release();
				visualizationComponent = nullptr;
			}
		};

	protected:
		virtual CoroutineTask<void> onInit() override;

		virtual void onUninit() {
			uninitSegmentComponent2D();
			__super::onUninit();
		};

		virtual void updateSize() override;

	public:
		SegmentComponent2D(NotNull<Entity2D> owner, World2D& world):BodyComponent2D(owner, world) {}
	
		~SegmentComponent2D() {
			if (IsInitialized)
				uninitSegmentComponent2D();
		}
	};
}
