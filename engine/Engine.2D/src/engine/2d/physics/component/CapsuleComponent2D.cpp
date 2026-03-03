#include "ghe2dpch.h"
#include "CapsuleComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& CapsuleComponent2D::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<CapsuleComponent2D>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<CapsuleComponent2D>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void CapsuleComponent2D::onInit() {
		if (isVisualized) {
			if (visualizationComponent) {
				Components.remove(visualizationComponent);
				visualizationComponent->release();
			}
			visualizationComponent = ghnew VisualizationComponent2D();
			visualizationComponent->Mesh = IntrusivePointer<Mesh>(Owner->Context->makeSpriteMesh()).get();
			visualizationComponent->Material = IntrusivePointer<Material>(Owner->Context->makeCapsuleVisualizationMaterial()).get();
			Components.add(visualizationComponent);
		}
		__super::onInit();

		b2Capsule capsule;
		capsule.radius = 1;
		capsule.center1 = { 0, -0.5 };
		capsule.center2 = { 0, 0.5 };
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreateCapsuleShape(Id, &shapeDef, &capsule);
	}

	void CapsuleComponent2D::updateSize() {
		b2Capsule capsule;
		float r = fabs(scale.x * size.Width) / 2;
		float h = std::max(0.001f, fabs(scale.y * size.Height) - 2 * r);
		capsule.radius = r;
		capsule.center1 = { 0, -h / 2 };
		capsule.center2 = { 0, h / 2 };
		b2Shape_SetCapsule(shapeId, &capsule);
	}
}
