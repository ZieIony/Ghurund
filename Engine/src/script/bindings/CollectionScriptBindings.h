#pragma once

#include "ScriptBindings.h"
#include "core/collection/Array.h"
#include "core/collection/PointerMap.h"
#include "core/collection/PointerList.h"

namespace Ghurund {

    class ListScriptBindings:ScriptBindings<List> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<List>::registerRefClass(engine, "List");
        }
    };

    class PointerListScriptBindings:ScriptBindings<PointerList> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<PointerList>::registerRefClass(engine, "PointerList");
        }
    };

    class ArrayScriptBindings:ScriptBindings<Array> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Array>::registerRefClass(engine, "Array");
        }
    };

    class PointerArrayScriptBindings:ScriptBindings<PointerArray> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<PointerArray>::registerRefClass(engine, "PointerArray");
        }
    };

    class MapScriptBindings:ScriptBindings<Map> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Map>::registerRefClass(engine, "Map");
        }
    };

    class PointerMapScriptBindings:ScriptBindings<PointerMap> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<PointerMap>::registerRefClass(engine, "PointerMap");
        }
    };

}