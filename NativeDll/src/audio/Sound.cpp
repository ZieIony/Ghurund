#include "audio/Sound.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Sound *Sound_new() {
    return new Sound();
}
