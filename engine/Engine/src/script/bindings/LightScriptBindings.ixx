module;

#include "entity/light/Light.h"
#include "core/reflection/Type.h"

export module Ghurund.Engine.Script.Bindings.LightScriptBindings;

import Ghurund.Engine.Script.Bindings.ScriptBindings;

export namespace Ghurund {

    class LightScriptBindings:ScriptBindings<Light> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Light>::registerRefClass(engine, Light::GET_TYPE().Name.Data);
        }
    };

}