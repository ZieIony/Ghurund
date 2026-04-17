#include "ghe2dpch.h"
#include "BoxComponent2D.h"

#include "engine/2d/scene/Entity2D.h"
#include "engine/2d/World2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& BoxComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<BoxComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	CoroutineTask<void> BoxComponent2D::onInit() {
		if (isVisualized) {
			if (visualizationComponent) {
				Components.remove(visualizationComponent);
				visualizationComponent->release();
			}
			visualizationComponent = Owner->makeComponent<VisualizationComponent2D>();
			visualizationComponent->Mesh = IntrusivePointer<Mesh>(Owner->World.context->makeSpriteMesh()).get();
			visualizationComponent->Material = (co_await Owner->World.context->makeBoxVisualizationMaterial()).get();
			Components.add(visualizationComponent);
		}
		co_await __super::onInit();
	
		b2Polygon box = b2MakeBox(fabs(scale.x * size.Width) / 2, fabs(scale.y * size.Height) / 2);
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreatePolygonShape(Id, &shapeDef, &box);
	}

	void BoxComponent2D::updateSize() {
		b2Polygon box = b2MakeBox(fabs(scale.x * size.Width) / 2, fabs(scale.y * size.Height) / 2);
		b2Shape_SetPolygon(shapeId, &box);
	}
}
