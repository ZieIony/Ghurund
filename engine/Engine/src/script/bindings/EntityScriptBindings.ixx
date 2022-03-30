export module Ghurund.Engine.Script.Bindings.EntityScriptBindings;

import Ghurund.Engine.Entity.Entity;
import Ghurund.Engine.Script.Bindings.ScriptBindings;

export namespace Ghurund {

    class EntityScriptBindings:ScriptBindings<Entity> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            //ScriptBindings<Entity>::registerRefClass(engine, Type::ENTITY.Name);
        }
    };

}