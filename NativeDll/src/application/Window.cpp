#include "application/Window.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Window *Window_new() {
    return new Window();
}

extern "C" __declspec(dllexport) void Window_init(Window *_this, HWND handle) {
    _this->init(handle);
}

extern "C" __declspec(dllexport) void Window_uninit(Window *_this) {
    _this->uninit();
}

extern "C" __declspec(dllexport) void Window_updateSize(Window *_this) {
    _this->updateSize();
}
