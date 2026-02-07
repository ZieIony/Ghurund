#include "ghe2dpch.h"
#include "BodyComponent2D.h"

namespace Ghurund::Engine::_2D {
	void BodyComponent2D::draw(RenderGroup& group, const XMFLOAT4X4& parentTransformation) {
		XMFLOAT4X4 world;
		auto parent = XMLoadFloat4x4(&parentTransformation);
		auto scaling = XMMatrixScaling(Size.Width, Size.Height, 1);
		auto rotation = XMMatrixRotationZ(Rotation);
		auto translation = XMMatrixTranslation(Position.x, Position.y, 0);
		auto w = XMMatrixTranspose(parent * scaling * rotation * translation);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMVector4Transform(XMVectorZero(), w));
		XMStoreFloat4x4(&world, w);

		if (mesh && material) {
			mesh->addReference();
			material->addReference();

			inputs.Transformation = world;

			group.objects.add(DrawPacket{
				IntrusivePointer<Ghurund::Engine::Mesh>(mesh),
				IntrusivePointer<Ghurund::Engine::Material>(material),
				pos
				});
		}

		__super::draw(group, world);
	}
}
