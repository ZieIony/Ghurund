#pragma once

#include "ScriptBindings.h"
#include "game/entity/light/Light.h"

namespace Ghurund {

    class LightScriptBindings:ScriptBindings<Light> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Light>::registerRefClass(engine, Light::TYPE.Name);
        }
    };

}