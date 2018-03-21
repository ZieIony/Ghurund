#include "application/Window.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Window *Window_new() {
    return new Window();
}

extern "C" __declspec(dllexport) void Window_init(Window *window, HWND handle) {
    window->init(handle);
}

extern "C" __declspec(dllexport) void Window_uninit(Window *window) {
    window->uninit();
}
