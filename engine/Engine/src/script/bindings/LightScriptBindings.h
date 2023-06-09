#pragma once

#include "core/reflection/Type.h"

#include "entity/light/Light.h"
#include "ScriptBindings.h"

namespace Ghurund {

    class LightScriptBindings:ScriptBindings<Light> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Light>::registerRefClass(engine, Light::GET_TYPE().Name.Data);
        }
    };

}