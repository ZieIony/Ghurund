#pragma once

#include "BodyComponent2D.h"
#include "engine/2d/scene/Entity2D.h"
#include <engine/2d/physics/World2D.h>

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

		inline void uninitBoxComponent2D() {
			if (visualizationComponent) {
				Components.remove(visualizationComponent);
				visualizationComponent->release();
				visualizationComponent = nullptr;
			}
		};

	protected:
		virtual void onInit();

		virtual void onUninit() {
			uninitBoxComponent2D();
			__super::onUninit();
		};

		virtual void updateSize() override;

	public:
		~BoxComponent2D() {
			if (IsInitialized)
				uninitBoxComponent2D();
		}

		//inline void setMass(float massKg) {
		//	b2Shape_SetDensity()
		//}
	};
}
