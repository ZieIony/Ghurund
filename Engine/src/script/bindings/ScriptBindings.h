#pragma once

#include "collection/ASCIIString.h"
#include "core/StaticClass.h"

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

        static void registerValueClass(asIScriptEngine& engine, const char* name) {
            auto r = engine.RegisterObjectType(name, sizeof(Type), asOBJ_VALUE | asGetTypeTraits<Type>()); assert(r >= 0);

            r = engine.RegisterObjectBehaviour(name, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(constructor), asCALL_CDECL_OBJLAST); assert(r >= 0);
            r = engine.RegisterObjectBehaviour(name, asBEHAVE_CONSTRUCT, A("void f(const ") + name + " &in)", asFUNCTION(copyConstructor), asCALL_CDECL_OBJLAST); assert(r >= 0);
            r = engine.RegisterObjectBehaviour(name, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(destructor), asCALL_CDECL_OBJLAST); assert(r >= 0);
        }

        static void registerRefClassUninstantiable(asIScriptEngine& engine, const char* name) {
            engine.RegisterObjectType(name, sizeof(Type), asOBJ_REF);

            engine.RegisterObjectBehaviour(name, asBEHAVE_ADDREF, "void f()", asMETHOD(Type, addReference), asCALL_THISCALL);
            engine.RegisterObjectBehaviour(name, asBEHAVE_RELEASE, "void f()", asMETHOD(Type, release), asCALL_THISCALL);
        }

        static void registerRefClass(asIScriptEngine& engine, const char* name) {
            registerRefClassUninstantiable(engine, name);

            engine.RegisterObjectBehaviour(name, asBEHAVE_FACTORY, A(name) + "@ f()", asFUNCTION(typeFactory), asCALL_CDECL);
        }
    };

}