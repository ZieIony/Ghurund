#pragma once

#include "engine/entity/3d/Drawable3DComponent.h"

#include "ScriptBindings.h"

namespace Ghurund::Engine {

    class ModelScriptBindings:ScriptBindings<Drawable3DComponent> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            //ScriptBindings<DrawableComponent>::registerRefClass(engine, DrawableComponent::GET_TYPE().Name);
        }
    };

}