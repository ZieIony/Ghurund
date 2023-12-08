#pragma once

#include "core/application/Feature.h"
#include "core/Timer.h"
#include "core/collection/PointerList.h"

#include <atomic>

#include "angelscript.h"
#include "angelscript/scriptmath.h"

#include "Script.h"
#include "StringFactory.h"
#include "ScriptComponent.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class ScriptEngine: public Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ScriptEngine::GET_TYPE();
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

        virtual void onInit() override;

        virtual void onUninit() override {
            if (engine)
                engine->ShutDownAndRelease();
        }

        asIScriptModule* makeModule() {
            std::string moduleName("module");
            moduleName += moduleIndex++;
            return engine->GetModule(moduleName.c_str(), asGM_ALWAYS_CREATE);
        }

        asIScriptContext* createContext() {
            return engine->CreateContext();
        }

        void update(const uint64_t time);
    };
}