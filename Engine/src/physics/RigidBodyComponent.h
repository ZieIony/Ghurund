#pragma once

#include "ecs/Component.h"
#include "game/TransformComponent.h"
#include "physics/Physics.h"

#pragma warning(push, 0)
#include <PxShape.h>
#pragma warning(pop)

namespace Ghurund {
	using namespace physx;

	class RigidBodyComponent :public Component {
	private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(RigidBodyComponent);
        
        TransformComponent& transformComponent;
		PxShape* shape = nullptr;

		void finalize() {
			safeRelease2(shape);
		}

	protected:
		virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
			return Status::OK;
		}

		virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
			return Status::OK;
		}

	public:
		RigidBodyComponent(TransformComponent& transform) :transformComponent(transform) {
		}

		PxShape* getShape() {
			return shape;
		}

		void setShape(PxShape* shape) {
			setPointer2(this->shape, shape);
		}

		__declspec(property(get = getShape, put = setShape)) PxShape* Shape;

		inline static const Ghurund::Type& TYPE = TypeBuilder<RigidBodyComponent>(NAMESPACE_NAME, CLASS_NAME).withSupertype(Component::TYPE);

		virtual const Ghurund::Type& getType() const override {
			return TYPE;
		}
	};
}