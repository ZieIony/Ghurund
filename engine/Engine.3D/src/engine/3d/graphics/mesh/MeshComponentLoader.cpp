#include "ghe3dpch.h"
#include "MeshComponentLoader.h"

#include "engine/3d/graphics/mesh/MeshComponent.h"

namespace Ghurund::Engine::_3D {
	void MeshComponentLoader::loadComponent(
		NotNull<Scene> scene,
		NotNull<Entity> entity,
		const XMLElement& xml,
		const DirectoryPath& workingDir
	) {
		auto& component = entity->addComponent<MeshComponent>();

		auto meshPathAttr = xml.requireAttribute(L"mesh");
		auto meshPath = FilePath(meshPathAttr);
		auto meshCoroutine = resourceManager.load<Mesh>(meshPath, workingDir);
		meshCoroutine.resume();
		component.Mesh = meshCoroutine.Result.get();

		auto materialPathAttr = xml.requireAttribute(L"material");
		auto materialPath = FilePath(materialPathAttr);
		auto materialCoroutine = resourceManager.load<Material>(materialPath, workingDir);
		materialCoroutine.resume();
		component.Material = materialCoroutine.Result.get();
	}
}
