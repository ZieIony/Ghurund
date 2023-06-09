#pragma once

#include "graphics/DrawableComponent.h"

#include "ScriptBindings.h"

namespace Ghurund {

    class ModelScriptBindings:ScriptBindings<DrawableComponent> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            //ScriptBindings<DrawableComponent>::registerRefClass(engine, DrawableComponent::GET_TYPE().Name);
        }
    };

}