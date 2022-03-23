module;

#include "game/entity/Scene.h"

export module Ghurund.Engine.Script.Bindings.SceneScriptBindings;

import Ghurund.Engine.Script.Bindings.ScriptBindings;

export namespace Ghurund {

    class SceneScriptBindings:ScriptBindings<Scene> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Scene>::registerRefClass(engine, Scene::GET_TYPE().Name.Data);
        }
    };

}