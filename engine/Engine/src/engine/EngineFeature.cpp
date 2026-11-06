#include "ghepch.h"
#include "EngineFeature.h"

#include "ecs/SceneLoader.h"
#include "script/ScriptComponentLoader.h"
#include "ecs/NameComponentLoader.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& EngineFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<EngineFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

	void EngineFeature::uninitEngineFeature() {
		resourceManager.Loaders.remove<Scene>();
		sceneLoader.set(nullptr);
	}

	CoroutineTask<void> EngineFeature::onInit() {
		sceneLoader = makeIntrusive<Engine::SceneLoader>();
		sceneLoader->addComponentLoader(makeIntrusive<ScriptComponentLoader>(scriptManager).ref());
		sceneLoader->addComponentLoader(makeIntrusive<NameComponentLoader>().ref());
		resourceManager.Loaders.set<Scene>(sceneLoader.ref());
		co_return;
	}

	void EngineFeature::onDeinit() {
		uninitEngineFeature();
	}
}
