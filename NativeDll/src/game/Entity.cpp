#include "game/Entity.h"
#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) size_t Entity_getSubentities_Size(Entity *_this) {
    return _this->getSubentities().Size;
}

extern "C" __declspec(dllexport) Entity *Entity_getSubentities_get(Entity *_this, size_t index) {
    return _this->getSubentities().get(index);
}

extern "C" __declspec(dllexport) tchar *Entity_getName(Entity *_this) {
    return copyStr(_this->getName().getData());
}

extern "C" __declspec(dllexport) void Entity_setName(Entity *_this, const tchar *fileName) {
    _this->setName(fileName);
}

extern "C" __declspec(dllexport) const Float3 Entity_getPosition(Entity *_this) {
    return convertFloat(_this->getPosition());
}

extern "C" __declspec(dllexport) void Entity_setPosition(Entity *_this, XMFLOAT3 position) {
    _this->setPosition(position);
}

extern "C" __declspec(dllexport) const Float3 Entity_getRotation(Entity *_this) {
    return convertFloat(_this->getRotation());
}

extern "C" __declspec(dllexport) void Entity_setRotation(Entity *_this, XMFLOAT3 rotation) {
    _this->setRotation(rotation);
}

extern "C" __declspec(dllexport) const Float3 Entity_getScale(Entity *_this) {
    return convertFloat(_this->getScale());
}

extern "C" __declspec(dllexport) void Entity_setScale(Entity *_this, XMFLOAT3 scale) {
    _this->setScale(scale);
}
