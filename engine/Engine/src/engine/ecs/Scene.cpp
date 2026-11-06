#include "ghepch.h"
#include "Scene.h"

#include <engine/script/ScriptComponent.h>

namespace Ghurund::Engine {
	const Ghurund::Core::Type& Scene::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Scene>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
    
    void Scene::init() {
        for (auto [entityId, scriptComponent] : entityRegistry.view<ScriptComponent>().each()) {
            auto entity = Entity(entityRegistry, entityId);
            scriptComponent.Script->onInit(entity, *this);
        }

        dataSize.system = sizeof(*this);
        State = ResourceState::INITIALIZED;
    }
}
