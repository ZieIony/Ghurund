#include "audio/Sound.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Sound *Sound_new() {
    return new Sound();
}

extern "C" __declspec(dllexport) Status Sound_play(Sound *_this) {
    return _this->play();
}

extern "C" __declspec(dllexport) Status Sound_pause(Sound *_this) {
    return _this->pause();
}

extern "C" __declspec(dllexport) Status Sound_stop(Sound *_this) {
    return _this->stop();
}

extern "C" __declspec(dllexport) bool Sound_isPlaying(Sound *_this) {
    return _this->isPlaying();
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Sound_getFormats() {
    return &Sound::getFormats();
}
