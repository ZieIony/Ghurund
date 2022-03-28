module;

#pragma warning(push, 0)
#include <PxShape.h>
#pragma warning(pop)

export module Ghurund.Engine.Physics.RigidBodyComponent;

import Ghurund.Engine.Physics.Physics;

export namespace Ghurund::Physics {
	using namespace physx;

	class RigidBodyComponent {
	private:
		PxShape* shape = nullptr;

		void finalize() {
			safeRelease2(shape);
		}

	public:
		PxShape* getShape() {
			return shape;
		}

		void setShape(PxShape* shape) {
			setPointer2(this->shape, shape);
		}

		__declspec(property(get = getShape, put = setShape)) PxShape* Shape;
	};
}