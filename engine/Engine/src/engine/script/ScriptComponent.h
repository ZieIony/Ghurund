#pragma once

#include "Script.h"

namespace Ghurund::Engine {
    class ScriptComponent {
    private:
        Ghurund::Engine::Script* script = nullptr;

    public:
        ScriptComponent(Ghurund::Engine::Script* script) {
            Script = script;
        }

        Ghurund::Engine::Script* getScript() {
            return script;
        }

        void setScript(Ghurund::Engine::Script* script) {
            setPointer(this->script, script);
        }

        __declspec(property(get = getScript, put = setScript)) Ghurund::Engine::Script* Script;
    };
}