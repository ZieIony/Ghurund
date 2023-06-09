#include "ghpch.h"
#include "ScriptEngine.h"

#include "core/Exceptions.h"
#include "core/application/Application.h"
#include "core/reflection/TypeBuilder.h"

#include <angelscript.h>
#include <script/angelscript/scriptmath.h>

#include "bindings\CameraScriptBindings.h"
#include "bindings\CollectionScriptBindings.h"
#include "bindings\EntityScriptBindings.h"
#include "bindings\LightScriptBindings.h"
#include "bindings\MathScriptBindings.h"
#include "bindings\ModelScriptBindings.h"
#include "bindings\SceneScriptBindings.h"
#include "bindings\ScriptBindings.h"
#include "bindings\TimerScriptBindings.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& ScriptEngine::GET_TYPE() {

        static const Ghurund::Core::Type TYPE = TypeBuilder<ScriptEngine>(Ghurund::NAMESPACE_NAME, "ScriptEngine")
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ScriptEngine::messageCallback(const asSMessageInfo* msg, void* param) {
        const LogType* type = &LogType::ERR0R;
        if (msg->type == asMSGTYPE_WARNING)
            type = &LogType::WARNING;
        else if (msg->type == asMSGTYPE_INFORMATION)
            type = &LogType::INFO;
        auto text = std::format(_T("%s (%d, %d): %s\n"), AString(msg->section), msg->row, msg->col, AString(msg->message));
        Logger::log(*type, text.c_str());
    }

    void ScriptEngine::log(const std::string& str) {
        auto text = std::format(_T("%s\n"), AString(str.c_str()));
        Logger::log(LogType::INFO, text.c_str());
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