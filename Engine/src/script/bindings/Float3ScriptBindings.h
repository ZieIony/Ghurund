#pragma once

#include "ScriptBindings.h"
#include "graphics/Graphics.h"

namespace Ghurund {

    class Float2ScriptBindings:ScriptBindings<XMFLOAT2> {
    public:
        static void constructor(XMFLOAT2* _this, const float x, const float y) {
            new(_this) XMFLOAT2(x, y);
        }

        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<XMFLOAT2>::registerValueClass(engine, "float2");

            auto r = engine.RegisterObjectBehaviour("float2", asBEHAVE_CONSTRUCT, "void f(const float x, const float y)", asFUNCTION(constructor), asCALL_CDECL_OBJFIRST); assert(r >= 0);
        }
    };

    class Float3ScriptBindings:ScriptBindings<XMFLOAT3> {
    public:
        static void constructor(XMFLOAT3* _this, const float x, const float y, const float z) {
            new(_this) XMFLOAT3(x, y, z);
        }

        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<XMFLOAT3>::registerValueClass(engine, "float3");

            auto r = engine.RegisterObjectBehaviour("float3", asBEHAVE_CONSTRUCT, "void f(const float x, const float y, const float z)", asFUNCTION(constructor), asCALL_CDECL_OBJFIRST); assert(r >= 0);
        }
    };

    class Float4ScriptBindings:ScriptBindings<XMFLOAT4> {
    public:
        static void constructor(XMFLOAT4* _this, const float x, const float y, const float z, const float w) {
            new(_this) XMFLOAT4(x, y, z, w);
        }

        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<XMFLOAT4>::registerValueClass(engine, "float4");

            auto r = engine.RegisterObjectBehaviour("float4", asBEHAVE_CONSTRUCT, "void f(const float x, const float y, const float z, const float w)", asFUNCTION(constructor), asCALL_CDECL_OBJFIRST); assert(r >= 0);
        }
    };

    class Int2ScriptBindings:ScriptBindings<XMINT2> {
    public:
        static void constructor(XMINT2* _this, const int x, const int y) {
            new(_this) XMINT2(x, y);
        }

        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<XMINT2>::registerValueClass(engine, "int2");

            auto r = engine.RegisterObjectBehaviour("int2", asBEHAVE_CONSTRUCT, "void f(const int x, const int y)", asFUNCTION(constructor), asCALL_CDECL_OBJFIRST); assert(r >= 0);
        }
    };

}