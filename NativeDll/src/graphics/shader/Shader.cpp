#include "graphics/shader/Shader.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Shader *Shader_new() {
    return new Shader();
}

extern "C" __declspec(dllexport) char *Shader_getSourceCode(Shader *_this) {
    return copyStr(_this->getSourceCode());
}

extern "C" __declspec(dllexport) void Shader_setSourceCode(Shader *_this, const char *sourceCode) {
    _this->setSourceCode(sourceCode);
}

extern "C" __declspec(dllexport) char *Shader_compile(Shader *_this) {
    char *errorMessages = nullptr;
    _this->compile(&errorMessages);
    return errorMessages;
}

extern "C" __declspec(dllexport) void Shader_build(Shader *_this, ResourceContext *context) {
    _this->build(*context);
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Shader_getFormats() {
    return &Shader::getFormats();
}