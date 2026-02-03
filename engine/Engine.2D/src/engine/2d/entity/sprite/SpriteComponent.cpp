#include "ghe2dpch.h"
#include "SpriteComponent.h"

namespace Ghurund::Engine::_2D {
	void SpriteComponent::draw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		if (!mesh || !material)
			return;
		mesh->addReference();
		material->addReference();
		inputs.Position = parentPosition + Position;
		inputs.Size = { size.Width, size.Height };
		inputs.ColorTexture = colorTexture;
		group.objects.add(DrawPacket{
			IntrusivePointer<Ghurund::Engine::Mesh>(mesh),
			IntrusivePointer<Ghurund::Engine::Material>(material),
			XMFLOAT3(parentPosition.x + Position.x, parentPosition.y + Position.y, 0)
		});
	}
}
