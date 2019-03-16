#include "script/Script.h"

using namespace Ghurund;
using namespace std;

extern "C" __declspec(dllexport) ScriptEngine *ScriptEngine_new() {
    return new ScriptEngine();
}

extern "C" __declspec(dllexport) Status ScriptEngine_init(ScriptEngine *_this, Timer *timer) {
    return _this->init(*timer);
}

extern "C" __declspec(dllexport) Script *Script_new() {
    return new Script();
}

extern "C" __declspec(dllexport) char *Script_getSourceCode(Script *_this) {
    return copyStr(_this->getSourceCode());
}

extern "C" __declspec(dllexport) void Script_setSourceCode(Script *_this, const char *sourceCode) {
    _this->setSourceCode(sourceCode);
}

extern "C" __declspec(dllexport) char *Script_getEntryPoint(Script *_this) {
    return copyStr(_this->getEntryPoint());
}

extern "C" __declspec(dllexport) void Script_setEntryPoint(Script *_this, const char *entryPoint) {
    _this->setEntryPoint(entryPoint);
}

extern "C" __declspec(dllexport) Status Script_init(Script *_this, ScriptEngine *scriptEngine) {
    return _this->build(*scriptEngine);
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Script_getFormats() {
    return &Script::getFormats();
}