#pragma once

#include "ScriptBindings.h"
#include "game/entity/Model.h"

namespace Ghurund {

    class ModelScriptBindings:ScriptBindings<Model> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Model>::registerRefClass(engine, Type::MODEL.Name);
        }
    };

}