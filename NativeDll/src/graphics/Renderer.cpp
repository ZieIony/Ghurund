#include "graphics/Renderer.h"
#include "../Float3.h"

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

extern "C" __declspec(dllexport) void RenderStep_setOverrideMaterial(RenderStep* _this, Material *material) {
    _this->setOverrideMaterial(material);
}

extern "C" __declspec(dllexport) void RenderStep_setInvalidMaterial(RenderStep* _this, Material *material) {
    _this->setInvalidMaterial(material);
}

extern "C" __declspec(dllexport) void Renderer_render(Renderer* _this, Frame *frame) {
    _this->render(*frame);
}

extern "C" __declspec(dllexport) RenderingStatistics* Renderer_getStatistics(Renderer* _this) {
    return &_this->Statistics;
}

extern "C" __declspec(dllexport) List<RenderStep*>* Renderer_getSteps(Renderer* _this) {
    return &_this->getSteps();
}


extern "C" __declspec(dllexport) RenderStep* RenderStep_new() {
    return ghnew RenderStep();
}

extern "C" __declspec(dllexport) List<Entity*>* RenderStep_getEntities(RenderStep* _this) {
    return &_this->getEntities();
}

extern "C" __declspec(dllexport) void RenderStep_setCamera(RenderStep* _this, Camera* camera) {
    _this->setCamera(camera);
}

extern "C" __declspec(dllexport) void RenderStep_initParameters(RenderStep* _this, ParameterManager* manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) Model* RenderStep_pick(RenderStep* _this, Int2 mousePos) {
    return _this->pick(convertInt2(mousePos));
}
