#pragma once

#include "core/collection/List.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/Renderer.h"
#include "graphics/entity/Scene.h"
#include "core/input/EventConsumer.h"

namespace Ghurund {
    class Level:public EventConsumer {
    private:
        PointerList<Scene*> scenes;

    public:
        PointerList<Scene*>& getScenes() {
            return scenes;
        }

        __declspec(property(get = getScenes)) PointerList<Scene*>& Scenes;

        virtual void onInit() {}
        virtual void onUninit() {}
        virtual void onUpdate() {
            for (Scene* s : scenes)
                s->transform();
        }

        virtual void onDraw(CommandList& commandList) {
            for (Scene* s : scenes)
                s->render(commandList);
        }
    };
}