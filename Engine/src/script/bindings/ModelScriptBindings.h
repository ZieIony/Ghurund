#pragma once

#include "ScriptBindings.h"
#include "graphics/DrawableComponent.h"

namespace Ghurund {

    class ModelScriptBindings:ScriptBindings<DrawableComponent> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<DrawableComponent>::registerRefClass(engine, DrawableComponent::TYPE.Name);
        }
    };

}