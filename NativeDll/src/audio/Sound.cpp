#include "audio/Sound.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Sound *Sound_new() {
    return new Sound();
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Sound_getFormats() {
    return &Sound::getFormats();
}
