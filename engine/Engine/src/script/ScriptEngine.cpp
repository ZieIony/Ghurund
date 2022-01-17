#include "ghpch.h"
#include "ScriptEngine.h"

#include "core/Exceptions.h"
#include "core/application/Application.h"
#include "script/bindings/ScriptBindings.h"
#include "script/bindings/CameraScriptBindings.h"
#include "script/bindings/Float3ScriptBindings.h"
#include "script/bindings/TimerScriptBindings.h"
#include "script/bindings/LightScriptBindings.h"
#include "script/bindings/ModelScriptBindings.h"
#include "script/bindings/SceneScriptBindings.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund {

    const Ghurund::Core::Type& ScriptEngine::GET_TYPE() {

        static const Ghurund::Core::Type TYPE = TypeBuilder<ScriptEngine>("Ghurund", "ScriptEngine")
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ScriptEngine::messageCallback(const asSMessageInfo* msg, void* param) {
        const LogType* type = &LogType::ERR0R;
        if (msg->type == asMSGTYPE_WARNING)
            type = &LogType::WARNING;
        else if (msg->type == asMSGTYPE_INFORMATION)
            type = &LogType::INFO;
        Logger::log(*type, _T("%hs (%d, %d): %hs\n"), convertText<char, tchar>(AString(msg->section)), msg->row, msg->col, convertText<char, tchar>(AString(msg->message)));
    }

    void ScriptEngine::log(const std::string& str) {
        Logger::log(LogType::INFO, _T("%hs\n"), convertText<char, tchar>(AString(str.c_str())));
    }

    void ScriptEngine::onInit() {
        engine = asCreateScriptEngine();
        engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);

        StringFactory::RegisterStdString(engine, &stringFactory);
        RegisterScriptMath(engine);

        auto r = engine->RegisterGlobalFunction("void log(const string &in)", asFUNCTION(log), asCALL_CDECL);
        if (r < 0) {
            Logger::log(LogType::ERR0R, _T("Failed to register global function.\n"));
            throw CallFailedException();
        }

        Float2ScriptBindings::registerClass(*engine);
        Float3ScriptBindings::registerClass(*engine);
        Float4ScriptBindings::registerClass(*engine);
        Int2ScriptBindings::registerClass(*engine);

        CameraScriptBindings::registerClass(*engine);
        LightScriptBindings::registerClass(*engine);
        SceneScriptBindings::registerClass(*engine);
        ModelScriptBindings::registerClass(*engine);
        TimerScriptBindings::registerClass(*engine, &this->timer);
    }

    void ScriptEngine::update(const uint64_t time) {
        /*for (ScriptComponent* c : Components) {
            if (!c->Enabled)
                continue;
            Script* s = c->Script;
            if (s->Valid)
                s->execute();
        }*/
    }
}