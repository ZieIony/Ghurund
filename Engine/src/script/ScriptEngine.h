#pragma once

#include "application/Logger.h"
#include "StringFactory.h"
#include "core/Object.h"
#include "application/Timer.h"
#include "Script.h"
#include "core/collection/PointerList.h"
#include "ecs/System.h"
#include "ScriptComponent.h"

#include <atomic>

#include "angelscript.h"
#include "angelscript/scriptmath.h"

#ifdef _DEBUG

#ifdef _WIN64
#pragma comment(lib, "angelscript64d.lib")
#else
#pragma comment(lib, "angelscriptd.lib")
#endif

#else

#ifdef _WIN64
#pragma comment(lib, "angelscript64.lib")
#else
#pragma comment(lib, "angelscript.lib")
#endif

#endif

namespace Ghurund {
    class ScriptEngine: public Object, public System<ScriptComponent> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ScriptEngine);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ScriptEngine>();
		
		asIScriptEngine* engine = nullptr;
        asIScriptModule* mod = nullptr;
        StringFactory stringFactory;
        std::atomic<unsigned int> moduleIndex = 0;
        Timer* timer;

        static void messageCallback(const asSMessageInfo* msg, void* param) {
            LogType type = LogType::ERR0R;
            if (msg->type == asMSGTYPE_WARNING)
                type = LogType::WARNING;
            else if (msg->type == asMSGTYPE_INFORMATION)
                type = LogType::INFO;
            Logger::log(type, _T("%hs (%d, %d): %hs\n"), msg->section, msg->row, msg->col, msg->message);
        }

    public:
        ~ScriptEngine() {
            if (engine)
                engine->ShutDownAndRelease();
        }

        static void log(const std::string& str) {
            Logger::log(LogType::INFO, S(str.c_str()));
        }

        Status init(Timer& timer);

        asIScriptModule* makeModule() {
            string moduleName("module");
            moduleName += moduleIndex++;
            return engine->GetModule(moduleName.c_str(), asGM_ALWAYS_CREATE);
        }

        asIScriptContext* createContext() {
            return engine->CreateContext();
        }

        void update(float dt);

        inline static const Ghurund::Type& TYPE = TypeBuilder<ScriptEngine>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(Object::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}