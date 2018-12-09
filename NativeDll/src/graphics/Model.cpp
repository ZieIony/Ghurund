#include "game/entity/Model.h"

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
