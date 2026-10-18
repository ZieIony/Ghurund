#include "ghe3dpch.h"
#include "MeshComponent.h"

#include "engine/3d/scene/Entity3D.h"
#include "engine/3d/World3D.h"
#include "engine/3d/Graphics3DFeature.h"

namespace Ghurund::Engine::_3D {
	CoroutineTask<void> MeshComponent::onInit() {
		auto& resourceManager = Owner.World.app.ResourceManager;
		if (!Mesh) {
			auto cubeMesh = co_await resourceManager.load<Ghurund::Engine::Mesh>(Graphics3DFeature::MESH_CUBE);
			Mesh = cubeMesh.get();
		}
		if (!Material) {
			auto basicMaterial = co_await resourceManager.load<Ghurund::Engine::Material>(
				Graphics3DFeature::MATERIAL_FORWARD_LIT,
				DirectoryPath::getCurrentDirectory(),
				ResourceFormat::AUTO,
				{ .clone = true }
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
