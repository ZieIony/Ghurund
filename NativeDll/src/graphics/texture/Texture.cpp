#include "graphics/texture/Texture.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Texture *Texture_new() {
    return new Texture();
}

extern "C" __declspec(dllexport) Image *Texture_getImage(Texture *_this) {
    return _this->Image;
}