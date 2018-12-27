#include "game/entity/Model.h"
#include "game/entity/Models.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Model *Model_new() {
    return new Model();
}

extern "C" __declspec(dllexport) Mesh *Model_getMesh(Model *_this) {
    return _this->getMesh();
}

extern "C" __declspec(dllexport) void Model_setMesh(Model *_this, Mesh *mesh) {
    _this->setMesh(mesh);
}

extern "C" __declspec(dllexport) Material *Model_getMaterial(Model *_this) {
    return _this->getMaterial();
}

extern "C" __declspec(dllexport) void Model_setMaterial(Model *_this, Material *material) {
    _this->setMaterial(material);
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Model_getFormats() {
    return &Model::getFormats();
}

extern "C" __declspec(dllexport) TransformedEntity * Models_makeCube(ResourceContext *context, Material *material) {
    return Models::makeCube(*context, *material);
}

extern "C" __declspec(dllexport) TransformedEntity * Models_makePlane(ResourceContext *context, Material *material) {
    return Models::makePlane(*context, *material);
}

extern "C" __declspec(dllexport) TransformedEntity * Models_makeSphere(ResourceContext *context, Material *material) {
    return Models::makeSphere(*context, *material);
}
