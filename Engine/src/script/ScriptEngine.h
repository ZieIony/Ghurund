#pragma once

#include "core/Logger.h"
#include "StringFactory.h"
#include "core/Object.h"
#include "core/Timer.h"
#include "Script.h"

#include <atomic>

#include "angelscript.h"
#include "angelscript/scriptmath.h"

#ifdef _DEBUG
#pragma comment(lib, "angelscriptd.lib")
#else
#pragma comment(lib, "angelscript.lib")
#endif

namespace Ghurund {
    class ScriptEngine: public Object {
    private:
        asIScriptEngine* engine = nullptr;
        asIScriptModule* mod = nullptr;
        StringFactory stringFactory;
        std::atomic<unsigned int> moduleIndex=0;
        Timer *timer;
        PointerList<Script*> scripts;

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
            if(engine)
                engine->ShutDownAndRelease();
        }

        static void log(const std::string &str) {
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

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        PointerList<Script*>& getScripts() {
            return scripts;
        }

        __declspec(property(get = getScripts)) PointerList<Script*> &Scripts;

        void execute();
    };
}