#pragma once

#include "ScriptComponent.h"
#include "ScriptManager.h"

#include "core/xml/XMLElement.h"
#include "engine/ecs/ComponentLoader.h"
#include "engine/ecs/Entity.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ScriptComponentLoader:public ComponentLoader {
	private:
		ScriptManager& scriptManager;

	public:
		ScriptComponentLoader(ScriptManager& scriptManager):scriptManager(scriptManager) {}

		virtual const WString& getComponentName() const override {
			static WString name = L"ScriptComponent";
			return name;
		}

		virtual void loadComponent(
			NotNull<Scene> scene,
			NotNull<Entity> entity,
			const XMLElement& xml,
			const DirectoryPath& workingDir
		) override {
			auto scriptClassName = xml.requireAttribute(L"script");
			auto& scriptComponent = entity->addComponent<ScriptComponent>();
			auto script = IntrusivePointer<Script>(scriptManager.makeScript(scriptClassName));
			scriptComponent.Script = script.get();
		}
	};
}
