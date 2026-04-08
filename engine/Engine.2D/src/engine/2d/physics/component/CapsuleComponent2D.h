#pragma once

#include "BodyComponent2D.h"
#include "engine/2d/scene/Entity2D.h"
#include <engine/2d/physics/World2D.h>

#include <box2d.h>

namespace Ghurund::Engine::_2D {
	class CapsuleComponent2D:public BodyComponent2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CapsuleComponent2D::GET_TYPE();
#pragma endregion

	private:
		b2ShapeId shapeId;

		inline void uninitCapsuleComponent2D() {
			if (visualizationComponent) {
				Components.remove(visualizationComponent);
				visualizationComponent->release();
				visualizationComponent = nullptr;
			}
		};

	protected:
		virtual CoroutineTask<void> onInit() override;

		virtual void onUninit() {
			uninitCapsuleComponent2D();
			__super::onUninit();
		};

		virtual void updateSize() override;

	public:
		~CapsuleComponent2D() {
			if (IsInitialized)
				uninitCapsuleComponent2D();
		}
	};
}
