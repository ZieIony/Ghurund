#include "ghe2dpch.h"
#include "BaseSpriteComponent.h"

#include "engine/2d/World2D.h"

namespace Ghurund::Engine::_2D {
		const Ghurund::Core::Type& BaseSpriteComponent::GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<BaseSpriteComponent>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		CoroutineTask<void> BaseSpriteComponent::onInit() {
			co_await __super::onInit();
			Mesh = IntrusivePointer(Owner->World.context->makeSpriteMesh()).get();
			Material = (co_await Owner->World.context->makeSpriteMaterial()).get();
		}
		
		void BaseSpriteComponent::draw(RenderGroup& group) {
		if (mesh && material) {
			auto w = XMMatrixTranslation(offset.x, offset.y, 0) * XMMatrixScaling(size.Width, size.Height, 1) * XMLoadFloat4x4(&Owner->Transform.WorldTransformation);
			XMFLOAT4X4 world;
			XMStoreFloat4x4(&world, XMMatrixTranspose(w));

			inputs.Transformation = world;
			inputs.Tint = tint;
			inputs.Alpha = alpha;
			group.objects.add(DrawPacket(mesh, material, drawOrder));
		}

		__super::draw(group);
	}
}
