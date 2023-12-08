#pragma once

#include "core/reflection/TypeBuilder.h"
#include "Ghurund.Engine.h"

#pragma warning(push, 0)
#include <PxShape.h>
#pragma warning(pop)

#include "entity/TransformComponent.h"
#include "Physics.h"

namespace Ghurund::Physics {
	using namespace physx;
	using namespace Ghurund::Core;

	class PhysicsComponent {
	private:
        TransformComponent& transformComponent;
		PxShape* shape = nullptr;

		void finalize() {
			safeRelease2(shape);
		}

	protected:
		virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
			return Status::OK;
		}

		virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
			return Status::OK;
		}

	public:
		PhysicsComponent(TransformComponent& transform) :transformComponent(transform) {}

		PxShape* getShape() {
			return shape;
		}

		void setShape(PxShape* shape) {
			setPointer2(this->shape, shape);
		}

		__declspec(property(get = getShape, put = setShape)) PxShape* Shape;
	};
}