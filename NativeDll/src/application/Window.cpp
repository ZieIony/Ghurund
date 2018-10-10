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

extern "C" __declspec(dllexport) void Window_updateSize(Window *window) {
    window->updateSize();
}

extern "C" __declspec(dllexport) void Window_initParameters(Window *window, ParameterManager *parameterManager) {
    window->initParameters(*parameterManager);
}

extern "C" __declspec(dllexport) void Window_fillParameters(Window *window) {
    window->fillParameters();
}
