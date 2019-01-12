#include "graphics/Renderer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Renderer *Renderer_new() {
    return new Renderer();
}

extern "C" __declspec(dllexport) void Renderer_init(Renderer *_this, Graphics *graphics, Window *window) {
    _this->init(*graphics, *window);
}

extern "C" __declspec(dllexport) CommandList *Renderer_startFrame(Renderer *_this) {
    return &_this->startFrame();
}

extern "C" __declspec(dllexport) void Renderer_finishFrame(Renderer *_this) {
    _this->finishFrame();
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

extern "C" __declspec(dllexport) void Renderer_draw(Renderer *_this, Camera *camera, Entity *entity, ParameterManager *parameterManager, Material *overrideMaterial, Material *invalidMaterial) {
    _this->draw(*camera, *entity, *parameterManager, overrideMaterial, invalidMaterial);
}
