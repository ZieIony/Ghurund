#include "ghe3dpch.h"
#include "MeshComponent.h"

#include "engine/3d/Graphics3DFeature.h"

namespace Ghurund::Engine::_3D {
	CoroutineTask<void> MeshComponent::init(ResourceManager& resourceManager) {
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
}
