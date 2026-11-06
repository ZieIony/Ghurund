#pragma once

#include <core/io/FilePath.h>
#include <core/xml/XMLElement.h>
#include <engine/ecs/ComponentLoader.h>
#include <engine/ecs/Entity.h>

namespace Ghurund::Engine::_3D {

	class MeshComponentLoader:public ComponentLoader {
	private:
		ResourceManager& resourceManager;

	public:
		MeshComponentLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}

		virtual const WString& getComponentName() const override {
			static WString name = L"MeshComponent";
			return name;
		}

		virtual void loadComponent(
			NotNull<Scene> scene,
			NotNull<Entity> entity,
			const XMLElement& xml,
			const DirectoryPath& workingDir
		) override;
	};
}
