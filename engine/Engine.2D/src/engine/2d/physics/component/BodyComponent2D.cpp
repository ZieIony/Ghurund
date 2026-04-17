#include "ghe2dpch.h"
#include "BodyComponent2D.h"

#include "engine/2d/physics/Simulation2D.h"
#include "engine/2d/World2D.h"

namespace Ghurund::Engine::_2D {
		const Ghurund::Core::Type& BodyComponent2D::GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<BodyComponent2D>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		CoroutineTask<void> BodyComponent2D::onInit() {
			co_await __super::onInit();
			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.position = { 0.0f, 0.0f };
			id = b2CreateBody(simulation.Id, &bodyDef);
		}
		
		BodyComponent2D::BodyComponent2D(NotNull<Entity2D> owner, World2D& world):BaseTransformComponent2D(owner, world), simulation(*world.simulation) {}

		void BodyComponent2D::update(const XMFLOAT4X4& parentTransformation, const Timer& timer) {
		__super::update(parentTransformation, timer);
		if (visualizationComponent) {
			XMFLOAT4X4 world;
			auto w = XMMatrixScaling(size.Width, size.Height, 1) * XMLoadFloat4x4(&worldTransformation);
			XMStoreFloat4x4(&world, w);
			visualizationComponent->Transformation = world;
			visualizationComponent->Extents = { Size.Width / 2, Size.Height / 2 };
		}
	}
}
