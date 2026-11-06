#include "ghepch.h"
#include "SceneLoader.h"

#include <engine/ecs/Entity.h>

namespace Ghurund::Engine {
	void SceneLoader::loadEntity(
		Scene& resource,
		const XMLElement& entityElement,
		const DirectoryPath& workingDir
	) {
		auto entity = resource.spawnEntity<Entity>();
		for (auto& component : entityElement.children) {
			auto it = componentLoaders.find(component->name);
			if (it == componentLoaders.end())
				throw InvalidStateException("component loader not found");
			it->value->loadComponent(resource, entity, component.ref(), workingDir);
		}
	}

	CoroutineTask<void> SceneLoader::load_internal(
		Scene& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		checkXmlRoot(xml, L"Scene", Scene::FORMAT_XML);

		for (auto& entityElement : xml.children) {
			if (entityElement->name != L"Entity")
				continue;

			loadEntity(resource, entityElement.ref(), workingDir);
		}

		resource.init();
		co_return;
	}

	void SceneLoader::save_internal(
		Scene& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOptions options
	) const {
	}
}
