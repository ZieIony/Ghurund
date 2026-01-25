#pragma once

#include "core/reflection/TypeBuilder.h"
#include "Ghurund.Engine.h"

#pragma warning(push, 0)
#include <PxShape.h>
#pragma warning(pop)

#include "entity/TransformComponent.h"
#include "Physics.h"

namespace Ghurund {
	using namespace physx;
	using namespace Ghurund::Core;

	class PhysicsComponent {
	private:
        Transform3DComponent& transformComponent;
		PxShape* shape = nullptr;

		void finalize() {
			safeRelease2(shape);
		}

	public:
		PhysicsComponent(Transform3DComponent& transform) :transformComponent(transform) {}

		PxShape* getShape() {
			return shape;
		}

		void setShape(PxShape* shape) {
			setPointer2(this->shape, shape);
		}

		__declspec(property(get = getShape, put = setShape)) PxShape* Shape;
	};
}