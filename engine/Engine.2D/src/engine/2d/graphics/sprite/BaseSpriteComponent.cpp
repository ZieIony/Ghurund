#include "ghe2dpch.h"
#include "BaseSpriteComponent.h"

#include "engine/2d/World2D.h"
#include "engine/2d/Graphics2DFeature.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& BaseSpriteComponent::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<BaseSpriteComponent>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	CoroutineTask<void> BaseSpriteComponent::onInit() {
		Mesh = Owner.World.app.ResourceManager.get<Ghurund::Engine::Mesh>(Graphics2DFeature::MESH_SPRITE).get();;
		auto spriteMaterial = IntrusivePointer<Ghurund::Engine::Material>(
			Owner.World.app.ResourceManager.get<Ghurund::Engine::Material>(Graphics2DFeature::MATERIAL_SPRITE)->clone()
		);
		Material = spriteMaterial.get();
		co_return;
	}

	void BaseSpriteComponent::queueDraw(RenderGroup& group) {
		if (!mesh || !material)
			return;

		auto w = XMMatrixTranslation(offset.x, offset.y, 0) * XMMatrixScaling(size.Width, size.Height, 1) * XMLoadFloat4x4(&Owner.Transform.WorldTransformation);
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&world, XMMatrixTranspose(w));

		inputs.Transformation = world;
		inputs.Tint = tint;
		inputs.Alpha = alpha;
		group.objects.add(DrawPacket(mesh, material, drawOrder));
	}
}
