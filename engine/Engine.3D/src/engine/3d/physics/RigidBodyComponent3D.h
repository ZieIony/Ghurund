#pragma once

#include "Physics.h"

#include "engine/3d/scene/component/Component3D.h"

#pragma warning(push, 0)
#include <PxShape.h>
#pragma warning(pop)

namespace Ghurund::Engine::_3D {
	using namespace physx;

	class RigidBodyComponent3D:public Component3D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = RigidBodyComponent3D::GET_TYPE();
#pragma endregion

	private:
		PxShape* shape = nullptr;

		void finalize() {
			safeRelease2(shape);
		}

	public:
		BodyComponent3D(NotNull<Entity3D> owner, World3D& world);
		
		PxShape* getShape() {
			return shape;
		}

		void setShape(PxShape* shape) {
			setPointer2(this->shape, shape);
		}

		__declspec(property(get = getShape, put = setShape)) PxShape* Shape;
	
		virtual void fixedUpdate(const Timer& timer) override;
	};
}
