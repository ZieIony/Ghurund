#pragma once

#include "core/application/Application.h"
#include "engine/audio/AudioFeature.h"
#include "engine/graphics/GraphicsFeature.h"
#include "engine/graphics/GraphicsFeatureFactory.h"
#include "engine/audio/AudioFeatureFactory.h"
#include "engine/game/system/System.h"
#include "engine/game/system/SystemCollection.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class GameApplication:public Application {
    private:
        GameObjectUpdateCollection gameObjects;
        SystemCollection systems = gameObjects;
        List<GameObject> preFixedUpdateQueue, postFixedUpdateQueue;
        List<GameObject> preUpdateQueue, postUpdateQueue;

    protected:
        virtual void onInit() override {
            __super::onInit();
            systems.init();
        }

        virtual void onUninit() override {
            systems.uninit();
            __super::onUninit();
        }

        virtual void onFixedUpdate() override {
            gameObjects.preFixedUpdate(Timer);
            __super::onFixedUpdate();
            gameObjects.postFixedUpdate(Timer);
        }

        virtual void onUpdate() override {
            gameObjects.preUpdate(Timer);
            __super::onUpdate();
            gameObjects.postUpdate(Timer);
        }

    public:
        GameApplication() {
            Features.add<GraphicsFeature, GraphicsFeatureFactory>();
            Features.add<AudioFeature, AudioFeatureFactory>();
        }

        inline GameObjectUpdateCollection& getGameObjects() {
            return gameObjects;
        }

        __declspec(property(get = getGameObjects)) GameObjectUpdateCollection& GameObjects;

        inline SystemCollection& getSystems() {
            return systems;
        }

        __declspec(property(get = getSystems)) SystemCollection Systems;
    };
}
