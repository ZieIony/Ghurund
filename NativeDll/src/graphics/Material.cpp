#include "graphics/Material.h"
#include "graphics/Materials.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Material *Material_new() {
    return new Material();
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Material_getFormats() {
    return &Material::getFormats();
}

extern "C" __declspec(dllexport) Shader *Material_getShader(Material *_this) {
    return _this->getShader();
}

extern "C" __declspec(dllexport) void Material_setShader(Material *_this, Shader *shader) {
    _this->setShader(shader);
}

extern "C" __declspec(dllexport) const PointerArray<Parameter*>* Material_getParameters(Material* _this) {
    return &_this->getParameters();
}

extern "C" __declspec(dllexport) void Material_initParameters(Material* _this, ParameterManager* manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) void Material_updateParameters(Material* _this) {
    _this->updateParameters();
}

extern "C" __declspec(dllexport) Material *Materials_makeChecker(ResourceContext *context) {
    return Materials::makeChecker(*context);
}

extern "C" __declspec(dllexport) Material *Materials_makeWireframe(ResourceContext *context) {
    return Materials::makeWireframe(*context);
}

extern "C" __declspec(dllexport) Material *Materials_makeOutline(ResourceContext *context) {
    return Materials::makeOutline(*context);
}

extern "C" __declspec(dllexport) Material *Materials_makeNormals(ResourceContext *context) {
    return Materials::makeNormals(*context);
}

extern "C" __declspec(dllexport) Material *Materials_makeInvalid(ResourceContext *context) {
    return Materials::makeInvalid(*context);
}
