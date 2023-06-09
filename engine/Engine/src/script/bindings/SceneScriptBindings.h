#pragma once

#include <format>

#include "entity/Scene.h"
#include "ScriptBindings.h"

namespace Ghurund {

    class SceneScriptBindings:ScriptBindings<Scene> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Scene>::registerRefClass(engine, Scene::GET_TYPE().Name.Data);
        }
    };

}