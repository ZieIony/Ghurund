#include "graphics/texture/Image.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Image *Image_new() {
    return new Image();
}

extern "C" __declspec(dllexport) UINT32 Image_getWidth(Image *_this) {
    return _this->getWidth();
}

extern "C" __declspec(dllexport) UINT32 Image_getHeight(Image *_this) {
    return _this->getHeight();
}

extern "C" __declspec(dllexport) UINT32 Image_getPixelSize(Image *_this) {
    return _this->getPixelSize();
}

extern "C" __declspec(dllexport) UINT32 Image_getRowPitch(Image *_this) {
    return _this->getRowPitch();
}

extern "C" __declspec(dllexport) void *Image_getData(Image *_this) {
    return _this->getData().Data;
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Image_getFormats() {
    return &Image::getFormats();
}
