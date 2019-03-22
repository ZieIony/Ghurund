#pragma once

#include "collection/ASCIIString.h"
#include "core/StaticClass.h"
#include "game/entity/Camera.h"

#include "angelscript.h"

namespace Ghurund {
    template <class Type>
    class ScriptBindings:StaticClass {
    public:
        static void constructor(Type* _this) {
            new(_this) Type();
        }

        static void copyConstructor(const Type& other, Type* _this) {
            new(_this) Type(other);
        }

        static void destructor(Type* _this) {
            _this->~Type();
        }

        static Type* typeFactory() {
            return new Type();
        }

        typedef ASCIIString A;
     
        static void registerValueClass(asIScriptEngine& engine, const Ghurund::Type& type) {
            auto r = engine.RegisterObjectType(type.Name, sizeof(Type), asOBJ_VALUE | asGetTypeTraits<Type>()); assert(r >= 0);

            r = engine.RegisterObjectBehaviour(type.Name, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(constructor), asCALL_CDECL_OBJLAST); assert(r >= 0);
            r = engine.RegisterObjectBehaviour(type.Name, asBEHAVE_CONSTRUCT, A("void f(const ") + type.Name + " &in)", asFUNCTION(copyConstructor), asCALL_CDECL_OBJLAST); assert(r >= 0);
            r = engine.RegisterObjectBehaviour(type.Name, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destructor), asCALL_CDECL_OBJLAST); assert(r >= 0);
        }

        static void registerRefClassUninstantiable(asIScriptEngine & engine, const Ghurund::Type & type) {
            engine.RegisterObjectType(type.Name, sizeof(Type), asOBJ_REF);

            engine.RegisterObjectBehaviour(type.Name, asBEHAVE_ADDREF, "void f()", asMETHOD(Type, addReference), asCALL_THISCALL);
            engine.RegisterObjectBehaviour(type.Name, asBEHAVE_RELEASE, "void f()", asMETHOD(Type, release), asCALL_THISCALL);
        }

        static void registerRefClass(asIScriptEngine & engine, const Ghurund::Type & type) {
            registerRefClassUninstantiable(engine, type);
         
            engine.RegisterObjectBehaviour(type.Name, asBEHAVE_FACTORY, A(type.Name) + "@ f()", asFUNCTION(typeFactory), asCALL_CDECL);
        }
    };

    class CameraScriptBindings:ScriptBindings<Camera> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Camera>::registerRefClass(engine, Type::CAMERA);

            auto r = engine.RegisterObjectMethod("Camera", "void setRotation(float yaw, float pitch, float roll=0)", asMETHOD(Camera, setRotation), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod("Camera", "void rotate(float yaw, float pitch, float roll=0)", asMETHOD(Camera, rotate), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod("Camera", "void setOrbit(float yaw, float pitch, float roll=0)", asMETHOD(Camera, setOrbit), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod("Camera", "void orbit(float yaw, float pitch, float roll=0)", asMETHOD(Camera, orbit), asCALL_THISCALL); assert(r >= 0);
        }
    };

    class TimerScriptBindings:ScriptBindings<Timer> {
    public:
        static void registerClass(asIScriptEngine& engine, Timer** timer) {

            engine.RegisterObjectType(Timer::TYPE.Name, sizeof(Timer), asOBJ_REF|asOBJ_NOCOUNT);
            auto r = engine.RegisterObjectMethod(Timer::TYPE.Name, "float getTime()", asMETHOD(Timer, getTime), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterGlobalProperty("Timer@ timer", timer); assert(r >= 0);
        }
    };
}