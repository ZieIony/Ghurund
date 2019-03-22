#include "ScriptEngine.h"
#include "ScriptBindings.h"

namespace Ghurund {
    const Ghurund::Type& ScriptEngine::TYPE = Ghurund::Type([]() {return ghnew ScriptEngine(); }, "ScriptEngine");
  
    Status ScriptEngine::init(Timer& timer) {
        this->timer = &timer;

        engine = asCreateScriptEngine();
        engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);

        StringFactory::RegisterStdString(engine, &stringFactory);
        RegisterScriptMath(engine);

        auto r = engine->RegisterGlobalFunction("void log(const string &in)", asFUNCTION(log), asCALL_CDECL);
        if (r < 0)
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Failed to register global function.\n"));

        CameraScriptBindings::registerClass(*engine);
        TimerScriptBindings::registerClass(*engine, &this->timer);

        return Status::OK;
    }

    void ScriptEngine::execute() {
        for (Ghurund::Script* s : scripts) {
            if(s->Valid)
                s->execute();
        }
    }
}