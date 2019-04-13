#include "graphics/SwapChain.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) SwapChain* SwapChain_new() {
    return new SwapChain();
}

extern "C" __declspec(dllexport) void SwapChain_init(SwapChain* _this, Graphics *graphics, Window* window, unsigned int frameCount) {
    _this->init(*graphics, *window, frameCount);
}

extern "C" __declspec(dllexport) void SwapChain_resize(SwapChain* _this, unsigned int width, unsigned int height) {
    _this->resize(width, height);
}

extern "C" __declspec(dllexport) Frame *SwapChain_getFrame(SwapChain* _this) {
    return &_this->getFrame();
}

extern "C" __declspec(dllexport) void SwapChain_present(SwapChain* _this) {
    _this->present();
}
