#pragma once

#include "core/application/Application.h"
#include "engine/audio/AudioFeature.h"
#include "engine/audio/AudioFeatureFactory.h"
#include "engine/ecs/SystemCollection.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class GameApplication:public Application {
    private:
        SystemCollection systems;

    protected:
        virtual void onFixedUpdate() override {
            __super::onFixedUpdate();
            systems.fixedUpdate(Timer);
        }

        virtual void onUpdate() override {
            __super::onUpdate();
            systems.update(Timer);
        }

    public:
        GameApplication() {
            Features.add<AudioFeature, AudioFeatureFactory>();
        }

        inline SystemCollection& getSystems() {
            return systems;
        }

        __declspec(property(get = getSystems)) SystemCollection Systems;
    };
}
