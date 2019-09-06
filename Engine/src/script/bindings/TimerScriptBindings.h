#pragma once

#include "ScriptBindings.h"
#include "application/Timer.h"

namespace Ghurund {

    class TimerScriptBindings:ScriptBindings<Timer> {
    public:
        static void registerClass(asIScriptEngine& engine, Timer** timer) {

            engine.RegisterObjectType(Timer::TYPE.Name, sizeof(Timer), asOBJ_REF | asOBJ_NOCOUNT);
            auto r = engine.RegisterObjectMethod(Timer::TYPE.Name, "float getTime()", asMETHOD(Timer, getTime), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterGlobalProperty("Timer@ timer", timer); assert(r >= 0);
        }
    };
}