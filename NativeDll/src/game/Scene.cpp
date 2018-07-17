#include "game/Scene.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Scene *Scene_new() {
    return new Scene();
}
