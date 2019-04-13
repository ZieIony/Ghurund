#include "script/Script.h"
#include "script/ScriptEngine.h"
#include "script/Scripts.h"
#include "../Float3.h"

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

extern "C" __declspec(dllexport) Status Script_build(Script *_this, ScriptEngine *scriptEngine) {
    return _this->build(*scriptEngine);
}

extern "C" __declspec(dllexport) Status Script_execute(Script *_this) {
    return _this->execute();
}

extern "C" __declspec(dllexport) int Script_getIntResult(Script *_this) {
    return _this->getIntResult();
}

extern "C" __declspec(dllexport) float Script_getFloatResult(Script *_this) {
    return _this->getFloatResult();
}

extern "C" __declspec(dllexport) Float3 Script_getFloat3Result(Script *_this) {
    return convertFloat3(*(XMFLOAT3*)_this->getObjectResult());
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Script_getFormats() {
    return &Script::getFormats();
}

extern "C" __declspec(dllexport) Script *Scripts_makeEmpty(Entity *param) {
    return Scripts::makeEmpty(param);
}

extern "C" __declspec(dllexport) Script *Scripts_make(Entity *param, const char *sourceCode) {
    return Scripts::make(param, sourceCode);
}
