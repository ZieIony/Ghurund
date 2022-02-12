#pragma once

#include "ecs/Component.h"
#include "game/TransformComponent.h"
#include "physics/Physics.h"

#pragma warning(push, 0)
#include <PxShape.h>
#pragma warning(pop)

namespace Ghurund::Physics {
	using namespace physx;

	class PhysicsComponent :public Component {
	private:
        TransformComponent& transformComponent;
		PxShape* shape = nullptr;

		void finalize() {
			safeRelease2(shape);
		}

		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(PhysicsComponent))
				.withSupertype(__super::GET_TYPE());

			return TYPE;
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

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

		virtual const Ghurund::Core::Type& getType() const override {
			return TYPE;
		}

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;
	};
}