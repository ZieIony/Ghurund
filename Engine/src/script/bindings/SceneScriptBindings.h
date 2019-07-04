#pragma once

#include "ScriptBindings.h"
#include "graphics/entity/Scene.h"

namespace Ghurund {

    class SceneScriptBindings:ScriptBindings<Scene> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Scene>::registerRefClass(engine, Type::SCENE.Name);
        }
    };

}