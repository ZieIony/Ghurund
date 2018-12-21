#include "game/entity/Light.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Light *Light_new() {
    return new Light();
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Light_getFormats() {
    return &Light::getFormats();
}
