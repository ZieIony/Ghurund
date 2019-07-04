#pragma once

#include "ScriptBindings.h"
#include "graphics/entity/Model.h"

namespace Ghurund {

    class ModelScriptBindings:ScriptBindings<Model> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Model>::registerRefClass(engine, Type::MODEL.Name);
        }
    };

}