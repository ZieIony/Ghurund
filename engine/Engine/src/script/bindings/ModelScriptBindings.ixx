module;

#include "graphics/DrawableComponent.h"

export module Ghurund.Engine.Script.Bindings.ModelScriptBindings;

import Ghurund.Engine.Script.Bindings.ScriptBindings;

export namespace Ghurund {

    class ModelScriptBindings:ScriptBindings<DrawableComponent> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            //ScriptBindings<DrawableComponent>::registerRefClass(engine, DrawableComponent::GET_TYPE().Name);
        }
    };

}