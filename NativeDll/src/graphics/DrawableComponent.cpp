#include "graphics/DrawableComponent.h"
#include "graphics/DrawableComponents.h"
#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) DrawableComponent* DrawableComponent_new() {
    return new DrawableComponent();
}

extern "C" __declspec(dllexport) Mesh* DrawableComponent_getMesh(DrawableComponent* _this) {
    return _this->getMesh();
}

extern "C" __declspec(dllexport) void DrawableComponent_setMesh(DrawableComponent* _this, Mesh* mesh) {
    _this->setMesh(mesh);
}

extern "C" __declspec(dllexport) Material* DrawableComponent_getMaterial(DrawableComponent* _this) {
    return _this->getMaterial();
}

extern "C" __declspec(dllexport) void DrawableComponent_setMaterial(DrawableComponent* _this, Material* material) {
    _this->setMaterial(material);
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*>* DrawableComponent_getFormats() {
    return &DrawableComponent::getFormats();
}

extern "C" __declspec(dllexport) DrawableComponent* DrawableComponents_makeCube(ResourceContext* context, Material* material) {
    return DrawableComponents::makeCube(*context, *material);
}

extern "C" __declspec(dllexport) DrawableComponent* DrawableComponents_makeCone(ResourceContext* context, Material* material) {
    return DrawableComponents::makeCone(*context, *material);
}

extern "C" __declspec(dllexport) DrawableComponent* DrawableComponents_makePlane(ResourceContext* context, Material* material) {
    return DrawableComponents::makePlane(*context, *material);
}

extern "C" __declspec(dllexport) DrawableComponent* DrawableComponents_makeSphere(ResourceContext* context, Material* material) {
    return DrawableComponents::makeSphere(*context, *material);
}
