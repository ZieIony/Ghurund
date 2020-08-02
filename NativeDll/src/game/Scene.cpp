#include "graphics/entity/Scene.h"
#include "graphics/entity/Scenes.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Scene *Scene_new() {
    return new Scene();
}

extern "C" __declspec(dllexport) PointerList<Entity*>* Scene_getEntities(Scene *_this) {
    return &_this->getEntities();
}

extern "C" __declspec(dllexport) const PointerArray<Parameter*> *Scene_getParameters(ParameterProvider *_this) {
    return &_this->getParameters();
}

extern "C" __declspec(dllexport) void Scene_initParameters(ParameterProvider *_this, ParameterManager *manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) void Scene_updateParameters(ParameterProvider *_this) {
    _this->updateParameters();
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Scene_getFormats() {
    return &Scene::getFormats();
}

extern "C" __declspec(dllexport) Scene *Scenes_makeEditor(ResourceContext *context) {
    return Scenes::makeEditor(*context);
}
