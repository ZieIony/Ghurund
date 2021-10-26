#pragma once

#include "StringFactory.h"
#include "application/Feature.h"
#include "core/Timer.h"
#include "Script.h"
#include "core/collection/PointerList.h"
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
    class ScriptEngine: public Feature {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

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

        virtual void init() override;

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