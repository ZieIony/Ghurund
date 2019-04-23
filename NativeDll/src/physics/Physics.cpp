#include "physics/Physics.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Physics *Physics_new() {
    return new Physics();
}

extern "C" __declspec(dllexport) Status Physics_init(Physics *physics) {
    return physics->init();
}
