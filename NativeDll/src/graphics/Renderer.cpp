#include "graphics/Renderer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Renderer *Renderer_new() {
    return new Renderer();
}

extern "C" __declspec(dllexport) void Renderer_init(Renderer *_this, Graphics *graphics, Window *window) {
    _this->init(*graphics, *window);
}

extern "C" __declspec(dllexport) shared_ptr<CommandList> *Renderer_startFrame(Renderer *_this) {
    return &(_this->startFrame());
}

extern "C" __declspec(dllexport) void Renderer_finishFrame(Renderer *_this) {
    _this->finishFrame();
}

extern "C" __declspec(dllexport) void Renderer_uninit(Renderer *_this) {
    _this->uninit();
}
