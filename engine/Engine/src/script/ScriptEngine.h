#pragma once

#include "StringFactory.h"
#include "application/Feature.h"
#include "core/Timer.h"
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

#include "reflection_c98597c1_bb96_4ddc_92c4_079c395065da.h"

namespace Ghurund {
    class ScriptEngine: public Feature, public System<ScriptComponent> {
        reflection_c98597c1_bb96_4ddc_92c4_079c395065da

    private:
		asIScriptEngine* engine = nullptr;
        asIScriptModule* mod = nullptr;
        StringFactory stringFactory;
        std::atomic<unsigned int> moduleIndex = 0;
        Timer* timer;

        static void messageCallback(const asSMessageInfo* msg, void* param);

    public:
        ScriptEngine(Timer& timer):timer(&timer) {}

        static void log(const std::string& str);

        virtual Status init() override;

        virtual void uninit() override {
            if (engine)
                engine->ShutDownAndRelease();
        }

        asIScriptModule* makeModule() {
            string moduleName("module");
            moduleName += moduleIndex++;
            return engine->GetModule(moduleName.c_str(), asGM_ALWAYS_CREATE);
        }

        asIScriptContext* createContext() {
            return engine->CreateContext();
        }

        void update(const uint64_t time);
    };
}