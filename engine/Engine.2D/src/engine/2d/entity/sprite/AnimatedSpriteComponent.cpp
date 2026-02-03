#include "ghe2dpch.h"
#include "AnimatedSpriteComponent.h"

namespace Ghurund::Engine::_2D {
	void AnimatedSpriteComponent::draw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		if (!mesh || !material)
			return;
		mesh->addReference();
		material->addReference();
		inputs.Position = parentPosition + Position;
		inputs.Size = size;
		inputs.ColorTexture = animation.CurrentTexture;
		group.objects.add(DrawPacket{
			IntrusivePointer<Ghurund::Engine::Mesh>(mesh),
			IntrusivePointer<Ghurund::Engine::Material>(material),
			XMFLOAT3(parentPosition.x + Position.x, parentPosition.y + Position.y, 0)
			});
	}
}