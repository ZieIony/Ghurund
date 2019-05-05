#pragma once

#include "ScriptBindings.h"
#include "game/entity/Entity.h"

namespace Ghurund {

    class EntityScriptBindings:ScriptBindings<Entity> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            //ScriptBindings<Entity>::registerRefClass(engine, Type::ENTITY.Name);
        }
    };

}