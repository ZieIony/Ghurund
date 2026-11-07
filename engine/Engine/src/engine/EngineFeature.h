#pragma once

#include "core/feature/Feature.h"
#include "core/reflection/Type.h"
#include "ecs/SceneLoader.h"
#include "engine/script/ScriptManager.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class EngineFeature: public Ghurund::Core::Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = EngineFeature::GET_TYPE();
#pragma endregion

    protected:
        ResourceManager& resourceManager;
        IntrusivePointer<SceneLoader> sceneLoader;
        ScriptManager scriptManager;

        void uninitEngineFeature();

    public:
        EngineFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        ~EngineFeature() {
            if (IsInitialized)
                uninitEngineFeature();
        }

        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onDeinit() override;

        inline SceneLoader& getSceneLoader() {
            return sceneLoader.ref();
        }

        __declspec(property(get = getSceneLoader)) SceneLoader& SceneLoader;

        inline ScriptManager& getScriptManager() {
            return scriptManager;
        }

        __declspec(property(get = getScriptManager)) ScriptManager& ScriptManager;
    };
}
