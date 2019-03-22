#pragma once

#include "Script.h"
#include "game/entity/Entity.h"

namespace Ghurund {

    class Scripts {
    private:
        Scripts() = delete;

    public:
        static Script* makeEmpty(Entity* entity) {
            typedef ASCIIString A;

            Script* script = ghnew Script();
            script->SourceCode = A("void main(") + entity->Type.Name + " &in " + A(entity->Type.Name).toLowerCase() + "){\n\n}";
            script->EntryPoint = A("void main(") + entity->Type.Name + " &in)";
            script->Arguments = {Argument(entity)};
            return script;
        }

        static Script* make(Entity* entity, const char *sourceCode) {
            typedef ASCIIString A;

            Script* script = ghnew Script();
            script->SourceCode = sourceCode;
            script->EntryPoint = A("void main(") + entity->Type.Name + " &in)";
            script->Arguments = {Argument(entity)};
            return script;
        }
    };
}