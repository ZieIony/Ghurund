#pragma once

#include "collection/List.h"
#include "game/entity/Scene.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/Renderer.h"
#include "graphics/RenderingBatch.h"
#include "input/EventConsumer.h"

namespace Ghurund {
    class Level:public EventConsumer {
    public:
        virtual void onInit() {}
        virtual void onUninit() {}
        virtual void onUpdate() {}
        virtual void onPreDraw(RenderingBatch &batch) {}
        virtual void onDraw(Renderer &renderer, ParameterManager &parameterManager) {}
    };
}