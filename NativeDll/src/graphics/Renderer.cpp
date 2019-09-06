#include "graphics/Renderer.h"
#include "MathUtils.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Renderer* Renderer_new() {
    return new Renderer();
}

extern "C" __declspec(dllexport) void Renderer_init(Renderer* _this, ResourceContext* resourceContext) {
    _this->init(*resourceContext);
}

extern "C" __declspec(dllexport) void Renderer_uninit(Renderer* _this) {
    _this->uninit();
}

extern "C" __declspec(dllexport) void Renderer_setClearColor(Renderer* _this, unsigned int color) {
    _this->setClearColor(ghnew XMFLOAT4(makeColor(color)));
}

extern "C" __declspec(dllexport) RenderingStatistics* Renderer_getStatistics(Renderer* _this) {
    return &_this->Statistics;
}
