module;

#include "entity/Entity.h"
#include "core/reflection/Type.h"

export module Ghurund.Engine.Script.Scripts;

import Ghurund.Engine.Script.Script;

export namespace Ghurund {

    class Scripts {
    private:
        Scripts() = delete;

    public:
        /*static Script* makeEmpty(Entity* entity) {
            typedef AString A;

            Script* script = ghnew Script();
            script->SourceCode = A("void main(") + entity->Type.Name + " &in " + A(entity->Type.Name).toLowerCase() + "){\n\n}";
            script->EntryPoint = A("void main(") + entity->Type.Name + " &in)";
            script->Arguments = {Argument(entity)};
            return script;
        }

        static Script* make(Entity* entity, const char* sourceCode) {
            typedef AString A;

            Script* script = ghnew Script();
            script->SourceCode = sourceCode;
            script->EntryPoint = A("void main(") + entity->Type.Name + " &in)";
            script->Arguments = {Argument(entity)};
            return script;
        }*/
    };
}