#pragma once

#include "entity/Entity.h"
#include "ScriptBindings.h"

namespace Ghurund::Engine {

    class EntityScriptBindings:ScriptBindings<Entity> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            //ScriptBindings<Entity>::registerRefClass(engine, Type::ENTITY.Name);
        }
    };

}