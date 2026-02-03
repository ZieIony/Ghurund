#include "ghe2dpch.h"
#include "BodyComponent2D.h"

namespace Ghurund::Engine::_2D {
	void BodyComponent2D::draw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		auto pos = parentPosition + Position;
		__super::draw(group, pos);
		if (!mesh || !material)
			return;
		mesh->addReference();
		material->addReference();
		inputs.Position = pos;
		inputs.Size = { Size.Width, Size.Height };
		group.objects.add(DrawPacket{
			IntrusivePointer<Ghurund::Engine::Mesh>(mesh),
			IntrusivePointer<Ghurund::Engine::Material>(material),
			XMFLOAT3(pos.x, pos.y, 0)
		});
	}
}
