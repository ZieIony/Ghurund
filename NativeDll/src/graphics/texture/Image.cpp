#include "graphics/texture/Image.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Image *Image_new() {
    return new Image();
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Image_getFormats() {
    return &Image::getFormats();
}