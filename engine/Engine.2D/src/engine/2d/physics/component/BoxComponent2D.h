#pragma once

#include "BodyComponent2D.h"

#include "engine/2d/scene/component/TransformComponent2D.h"

#include <box2d.h>

namespace Ghurund::Engine::_2D {
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
		FloatSize size = { 1, 1 };

		EventHandler<TransformComponent2D> scaleChangedHandler = [&](TransformComponent2D& transform) -> bool {
			updateShape();
			return true;
		};

		inline b2Polygon makeBox() {
			return b2MakeBox(fabs(scale.x * size.Width) / 2, fabs(scale.y * size.Height) / 2);
		}

		inline void updateShape() {
			b2Polygon box = makeBox();
			b2Shape_SetPolygon(shapeId, &box);
		}

		void uninitBoxComponent2D();;

	protected:
		virtual CoroutineTask<void> onInit() override;

		virtual void onUninit() {
			uninitBoxComponent2D();
			__super::onUninit();
		};

	public:
		BoxComponent2D(NotNull<Entity2D> owner, World2D& world):BodyComponent2D(owner, world) {}
	
		~BoxComponent2D() {
			if (IsInitialized)
				uninitBoxComponent2D();
		}

		inline const FloatSize& getSize() const {
			return size;
		}

		inline void setSize(const FloatSize& size) {
			if (this->size != size) {
				this->size = size;
				updateShape();
			}
		}

		__declspec(property(get = getSize, put = setSize)) const FloatSize& Size;

		//inline void setMass(float massKg) {
		//	b2Shape_SetDensity()
		//}

		virtual void update(const Timer& timer) override;
	};
}
