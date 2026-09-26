#include "ghe3dpch.h"
#include "MeshComponent.h"

#include "engine/3d/scene/Entity3D.h"
#include "engine/3d/World3D.h"
#include "engine/3d/Graphics3DFeature.h"

namespace Ghurund::Engine::_3D {
	CoroutineTask<void> MeshComponent::onInit() {
		if (!Mesh)
			Mesh = Owner.World.app.ResourceManager.get<Ghurund::Engine::Mesh>(Graphics3DFeature::MESH_CUBE).get();
		if (!Material) {
			auto basicMaterial = IntrusivePointer<Ghurund::Engine::Material>(
				Owner.World.app.ResourceManager.get<Ghurund::Engine::Material>(Graphics3DFeature::MATERIAL_FORWARD_LIT)->clone()
			);
			Material = basicMaterial.get();
		}
		co_return;
	}

	void MeshComponent::queueDraw(RenderGroup& group) {
		if (!mesh || !material)
			return;

		auto w = XMLoadFloat4x4(&Owner.Transform.WorldTransformation);
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&world, XMMatrixTranspose(w));

		inputs.Transformation = world;
		group.objects.add(DrawPacket(mesh, material, drawOrder));
	}
}
