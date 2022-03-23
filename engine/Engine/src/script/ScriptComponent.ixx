module;

#include "core/Pointer.h"

export module Ghurund.Engine.Script.ScriptComponent;

import Ghurund.Engine.Script.Script;

export namespace Ghurund {
    class ScriptComponent {
    private:
        Ghurund::Script* script = nullptr;

    public:
        ScriptComponent(Ghurund::Script* script) {
            Script = script;
        }

        Ghurund::Script* getScript() {
            return script;
        }

        void setScript(Ghurund::Script* script) {
            setPointer(this->script, script);
        }

        __declspec(property(get = getScript, put = setScript)) Ghurund::Script* Script;
    };
}