#include "ghe2dpch.h"
#include "CapsuleComponent2D.h"

#include "engine/2d/World2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& CapsuleComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<CapsuleComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void CapsuleComponent2D::uninitCapsuleComponent2D() {
		Owner->Transform.scaleChanged -= scaleChangedHandler;
		if (visualizationComponent) {
			Owner->Components.remove(visualizationComponent);
			visualizationComponent->release();
			visualizationComponent = nullptr;
		}
	}

	CoroutineTask<void> CapsuleComponent2D::onInit() {
		if (isVisualized) {
			if (visualizationComponent) {
				Owner->Components.remove(visualizationComponent);
				visualizationComponent->release();
			}
			visualizationComponent = Owner->makeComponent<VisualizationComponent2D>();
			visualizationComponent->Mesh = IntrusivePointer<Mesh>(Owner->World.context->makeSpriteMesh()).get();
			visualizationComponent->Material = (co_await Owner->World.context->makeCapsuleVisualizationMaterial()).get();
			Owner->Components.add(visualizationComponent);
		}
		co_await __super::onInit();

		b2Capsule capsule = makeCapsule();
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeId = b2CreateCapsuleShape(Id, &shapeDef, &capsule);

		Owner->Transform.scaleChanged += scaleChangedHandler;
	}
	
	void CapsuleComponent2D::update(const Timer& timer) {
		if (visualizationComponent) {
			XMFLOAT4X4 world;
			auto w = XMMatrixScaling(radius * 2, height, 1);
			if (BodyType == BodyType::STATIC) {
				auto rotation = XMMatrixRotationZ(Rotation / 180 * XM_PI);
				auto translation = XMMatrixTranslation(Position.x, Position.y, 0);
				w = w * rotation * translation;
			}
			w = w * XMLoadFloat4x4(&Owner->Transform.WorldTransformation);
			XMStoreFloat4x4(&world, w);
			visualizationComponent->Transformation = world;
			visualizationComponent->Extents = { radius, height / 2 };
		}
	}
}
