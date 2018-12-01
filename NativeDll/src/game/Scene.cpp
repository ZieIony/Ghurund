#include "game/entity/Scene.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Scene *Scene_new() {
    return new Scene();
}

extern "C" __declspec(dllexport) List<Entity*> *Scene_getEntities(Scene *_this) {
    return &_this->getEntities();
}

extern "C" __declspec(dllexport) Array<Parameter*> *Scene_getParameters(ParameterProvider *_this) {
    return &_this->getParameters();
}

extern "C" __declspec(dllexport) void Scene_initParameters(ParameterProvider *_this, ParameterManager *manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) void Scene_updateParameters(ParameterProvider *_this) {
    _this->updateParameters();
}
