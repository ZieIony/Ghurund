#include "game/entity/Model.h"
#include "game/entity/Models.h"
#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Model* Model_new() {
    return new Model();
}

extern "C" __declspec(dllexport) Mesh* Model_getMesh(Model* _this) {
    return _this->getMesh();
}

extern "C" __declspec(dllexport) void Model_setMesh(Model* _this, Mesh* mesh) {
    _this->setMesh(mesh);
}

extern "C" __declspec(dllexport) Material* Model_getMaterial(Model* _this) {
    return _this->getMaterial();
}

extern "C" __declspec(dllexport) void Model_setMaterial(Model* _this, Material* material) {
    _this->setMaterial(material);
}

extern "C" __declspec(dllexport) Float3 Model_getPosition(Model* _this) {
    return convertFloat3(_this->getPosition());
}

extern "C" __declspec(dllexport) void Model_setPosition(Model* _this, Float3 position) {
    _this->setPosition(convertFloat3(position));
}

extern "C" __declspec(dllexport) Float3 Model_getRotation(Model* _this) {
    return convertFloat3(_this->getRotation());
}

extern "C" __declspec(dllexport) void Model_setRotation(Model* _this, Float3 rotation) {
    _this->setRotation(convertFloat3(rotation));
}

extern "C" __declspec(dllexport) Float3 Model_getScale(Model* _this) {
    return convertFloat3(_this->getScale());
}

extern "C" __declspec(dllexport) void Model_setScale(Model* _this, Float3 scale) {
    _this->setScale(convertFloat3(scale));
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*>* Model_getFormats() {
    return &Model::getFormats();
}

extern "C" __declspec(dllexport) Model* Models_makeCube(ResourceContext* context, Material* material) {
    return Models::makeCube(*context, *material);
}

extern "C" __declspec(dllexport) Model* Models_makeCone(ResourceContext* context, Material* material) {
    return Models::makeCone(*context, *material);
}

extern "C" __declspec(dllexport) Model* Models_makePlane(ResourceContext* context, Material* material) {
    return Models::makePlane(*context, *material);
}

extern "C" __declspec(dllexport) Model* Models_makeSphere(ResourceContext* context, Material* material) {
    return Models::makeSphere(*context, *material);
}
