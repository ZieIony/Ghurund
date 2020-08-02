#include "editor/ThumbnailRenderer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ThumbnailRenderer* ThumbnailRenderer_new() {
    return new ThumbnailRenderer();
}

extern "C" __declspec(dllexport) void ThumbnailRenderer_init(ThumbnailRenderer* _this, ResourceContext* resourceContext, uint32_t width, uint32_t height) {
    _this->init(*resourceContext, width, height);
}

extern "C" __declspec(dllexport) Image* ThumbnailRenderer_renderDrawableComponent(ThumbnailRenderer* _this, DrawableComponent* drawableComponent) {
    Image* image;
    _this->render(*drawableComponent, image);
    return image;
}

extern "C" __declspec(dllexport) Image* ThumbnailRenderer_renderMesh(ThumbnailRenderer* _this, Mesh* mesh) {
    Image* image;
    _this->render(*mesh, image);
    return image;
}

extern "C" __declspec(dllexport) Image* ThumbnailRenderer_renderMaterial(ThumbnailRenderer* _this, Material* material) {
    Image* image;
    _this->render(*material, image);
    return image;
}
