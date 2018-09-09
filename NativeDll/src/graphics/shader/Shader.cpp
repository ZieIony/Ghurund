#include "graphics/shader/Shader.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Shader *Shader_new() {
    return new Shader();
}

extern "C" __declspec(dllexport) bool Shader_load(Shader *_this, ResourceManager *resourceManager, tchar *fileName) {
    return _this->load(*resourceManager, String(fileName))==Status::OK;
}

extern "C" __declspec(dllexport) bool Shader_save(Shader *_this, ResourceManager *resourceManager, tchar *fileName) {
    return _this->save(*resourceManager, fileName)==Status::OK;
}

extern "C" __declspec(dllexport) const tchar *Shader_getFileName(Shader *_this) {
    return copyStr(_this->getFileName().getData());
}

extern "C" __declspec(dllexport) void Shader_setFileName(Shader *_this, const tchar *fileName) {
    _this->setFileName(String(fileName));
}

/*extern "C" __declspec(dllexport) const char *Shader_getEntryPoint(shared_ptr<Shader> *_this) {
    return copyStrA((*_this)->getEntryPoint());
}

extern "C" __declspec(dllexport) void Shader_setEntryPoint(shared_ptr<Shader> *_this, const char *entryPoint) {
    (*_this)->setEntryPoint(entryPoint);
}

extern "C" __declspec(dllexport) const char *Shader_getCompilationTarget(shared_ptr<Shader> *_this) {
    return copyStrA((*_this)->getCompilationTarget());
}

extern "C" __declspec(dllexport) void Shader_setCompilationTarget(shared_ptr<Shader> *_this, const char *compilationTarget) {
    (*_this)->setCompilationTarget(compilationTarget);
}*/

extern "C" __declspec(dllexport) char *Shader_getSourceCode(Shader *_this) {
    return copyStrA(_this->getSourceCode());
}

extern "C" __declspec(dllexport) void Shader_setSourceCode(Shader *_this, const char *sourceCode) {
    _this->setSourceCode(sourceCode);
}

extern "C" __declspec(dllexport) char *Shader_compile(Shader *_this, const char *sourceCode) {
    char *errorMessages = nullptr;
    _this->setSourceCode(sourceCode);
    _this->compile(&errorMessages);
    return errorMessages;
}
