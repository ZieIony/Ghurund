#include "audio/Audio.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Audio *Audio_new() {
    return new Audio();
}

extern "C" __declspec(dllexport) Status Audio_init(Audio *audio) {
    return audio->init();
}

extern "C" __declspec(dllexport) void Audio_uninit(Audio *audio) {
    audio->uninit();
}
