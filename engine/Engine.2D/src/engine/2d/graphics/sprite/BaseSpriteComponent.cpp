#include "ghe2dpch.h"
#include "BaseSpriteComponent.h"

namespace Ghurund::Engine::_2D {
		const Ghurund::Core::Type& BaseSpriteComponent::GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<BaseSpriteComponent>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}
		
		void BaseSpriteComponent::draw(RenderGroup& group) {
		if (mesh && material) {
			auto w = XMMatrixScaling(size.Width, size.Height, 1) * XMLoadFloat4x4(&worldTransformation);
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
