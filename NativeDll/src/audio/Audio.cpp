#include "audio/Audio.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Audio *Audio_new() {
    return new Audio();
}

extern "C" __declspec(dllexport) void Audio_delete(Audio *_this) {
    delete _this;
}

extern "C" __declspec(dllexport) Status Audio_init(Audio *_this) {
    return _this->init();
}

extern "C" __declspec(dllexport) void Audio_uninit(Audio *_this) {
    _this->uninit();
}
