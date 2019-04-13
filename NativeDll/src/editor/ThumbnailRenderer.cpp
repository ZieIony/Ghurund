#include "editor/ThumbnailRenderer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ThumbnailRenderer* ThumbnailRenderer_new() {
    return new ThumbnailRenderer();
}

extern "C" __declspec(dllexport) void ThumbnailRenderer_init(ThumbnailRenderer* _this, ResourceManager* resourceManager, ResourceContext* resourceContext, UINT32 width, UINT32 height) {
    _this->init(*resourceManager, *resourceContext, width, height);
}

extern "C" __declspec(dllexport) Image* ThumbnailRenderer_renderModel(ThumbnailRenderer* _this, Model* model) {
    Image* image;
    _this->render(*model, image);
    return image;
}

extern "C" __declspec(dllexport) Image* ThumbnailRenderer_renderMesh(ThumbnailRenderer* _this, Mesh* mesh) {
    Image* image;
    _this->render(*mesh, image);
    return image;
}
