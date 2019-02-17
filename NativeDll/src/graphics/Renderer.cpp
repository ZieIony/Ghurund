#include "graphics/Renderer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Renderer *Renderer_new() {
    return new Renderer();
}

extern "C" __declspec(dllexport) void Renderer_init(Renderer *_this, Window *window, ResourceManager *resourceManager, ResourceContext *resourceContext) {
    _this->init(*window, *resourceManager, *resourceContext);
}

extern "C" __declspec(dllexport) void Renderer_uninit(Renderer *_this) {
    _this->uninit();
}

extern "C" __declspec(dllexport) void Renderer_resize(Renderer *_this, unsigned int width, unsigned int height) {
    _this->resize(width, height);
}

extern "C" __declspec(dllexport) void Renderer_setClearColor(Renderer *_this, unsigned int color) {
    _this->setClearColor(ghnew XMFLOAT4(makeColor(color)));
}

extern "C" __declspec(dllexport) void Renderer_render(Renderer *_this) {
    _this->render();
}

extern "C" __declspec(dllexport) RenderingStatistics *Renderer_getStatistics(Renderer *_this) {
    return &_this->Statistics;
}

extern "C" __declspec(dllexport) List<RenderStep*> *Renderer_getSteps(Renderer *_this) {
    return &_this->getSteps();
}
