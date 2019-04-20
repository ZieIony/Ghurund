#include "editor/ThumbnailRenderer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ThumbnailRenderer* ThumbnailRenderer_new() {
    return new ThumbnailRenderer();
}

extern "C" __declspec(dllexport) void ThumbnailRenderer_init(ThumbnailRenderer* _this, ResourceManager* resourceManager, ResourceContext* resourceContext, UINT32 width, UINT32 height) {
    _this->init(*resourceManager, *resourceContext, width, height);
}

extern "C" __declspec(dllexport) Image* ThumbnailRenderer_renderEntity(ThumbnailRenderer* _this, Entity* entity) {
    Image* image;
    _this->render(*entity, image);
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
