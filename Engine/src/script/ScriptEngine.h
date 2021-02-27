#pragma once

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
		asIScriptEngine* engine = nullptr;
        asIScriptModule* mod = nullptr;
        StringFactory stringFactory;
        std::atomic<unsigned int> moduleIndex = 0;
        Timer* timer;

        static void messageCallback(const asSMessageInfo* msg, void* param);

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        ~ScriptEngine() {
            if (engine)
                engine->ShutDownAndRelease();
        }

        static void log(const std::string& str);

        Status init(Timer& timer);

        asIScriptModule* makeModule() {
            string moduleName("module");
            moduleName += moduleIndex++;
            return engine->GetModule(moduleName.c_str(), asGM_ALWAYS_CREATE);
        }

        asIScriptContext* createContext() {
            return engine->CreateContext();
        }

        void update(const uint64_t time);

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}