#pragma once

#include "ComponentLoader.h"
#include "NameComponent.h"

#include "core/object/NotNull.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class NameComponentLoader:public ComponentLoader {
	public:
		virtual const WString& getComponentName() const {
			static WString name = L"NameComponent";
			return name;
		}

		virtual void loadComponent(
			NotNull<Scene> scene,
			NotNull<Entity> entity,
			const XMLElement& xml,
			const DirectoryPath& workingDir
		) override {
			auto& nameComponent = entity->addComponent<NameComponent>();
			nameComponent.name = xml.requireAttribute(L"name");
		}
	};
}
