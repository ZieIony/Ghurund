#include "ghe2dpch.h"
#include "AnimatedSpriteComponent.h"

namespace Ghurund::Engine::_2D {
	void AnimatedSpriteComponent::draw(RenderGroup& group, const XMFLOAT4X4& parentTransformation) {
		if (!mesh || !material)
			return;
		mesh->addReference();
		material->addReference();

		// TODO: don't compute this twice (here and in Transformed2DComponent)
		auto w = XMLoadFloat4x4(&parentTransformation) * XMLoadFloat4x4(&Transformation);
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&world, w);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMVector4Transform(XMVectorZero(), w));

		inputs.Transformation = world;
		inputs.Tint = tint;
		inputs.Alpha = alpha;
		inputs.ColorTexture = animation.CurrentTexture;
		group.objects.add(DrawPacket{
			IntrusivePointer<Ghurund::Engine::Mesh>(mesh),
			IntrusivePointer<Ghurund::Engine::Material>(material),
			pos
			});
	}
}