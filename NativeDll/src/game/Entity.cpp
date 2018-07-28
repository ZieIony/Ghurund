#include "game/Entity.h"
#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) List<Entity*> *Entity_getEntities(Entity *_this) {
    return &_this->getEntities();
}

extern "C" __declspec(dllexport) List<Parameter*> *Entity_getParameters(Entity *_this) {
    return &_this->getParameters();
}

extern "C" __declspec(dllexport) void Entity_initParameters(Entity *_this, ParameterManager *manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) void Entity_fillParameters(Entity *_this) {
    _this->fillParameters();
}

extern "C" __declspec(dllexport) EntityType Entity_getType(Entity *_this) {
    return _this->Type;
}

extern "C" __declspec(dllexport) tchar *Entity_getName(Entity *_this) {
    return copyStr(_this->getName().getData());
}

extern "C" __declspec(dllexport) void Entity_setName(Entity *_this, const tchar *fileName) {
    _this->setName(fileName);
}

extern "C" __declspec(dllexport) const Float3 Entity_getPosition(Entity *_this) {
    return convertFloat3(_this->getPosition());
}

extern "C" __declspec(dllexport) void Entity_setPosition(Entity *_this, XMFLOAT3 position) {
    _this->setPosition(position);
}

extern "C" __declspec(dllexport) const Float3 Entity_getRotation(Entity *_this) {
    return convertFloat3(_this->getRotation());
}

extern "C" __declspec(dllexport) void Entity_setRotation(Entity *_this, XMFLOAT3 rotation) {
    _this->setRotation(rotation);
}

extern "C" __declspec(dllexport) const Float3 Entity_getScale(Entity *_this) {
    return convertFloat3(_this->getScale());
}

extern "C" __declspec(dllexport) void Entity_setScale(Entity *_this, XMFLOAT3 scale) {
    _this->setScale(scale);
}

extern "C" __declspec(dllexport) void Entity_addEntity(Entity *_this, Entity *child) {
    _this->getEntities().add(child);
}

extern "C" __declspec(dllexport) void Entity_removeEntity(Entity *_this, Entity *child) {
    _this->getEntities().remove(child);
}