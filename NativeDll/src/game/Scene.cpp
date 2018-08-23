#include "game/Scene.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Scene *Scene_new() {
    return new Scene();
}

extern "C" __declspec(dllexport) List<Entity*> *Scene_getEntities(Scene *_this) {
    return &_this->getEntities();
}
