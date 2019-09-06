#include "ecs/Entity.h"
#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) const PointerArray<Parameter*>* ParameterProvider_getParameters(ParameterProvider* _this) {
    return &_this->getParameters();
}

extern "C" __declspec(dllexport) void ParameterProvider_initParameters(ParameterProvider* _this, ParameterManager* manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) void ParameterProvider_updateParameters(ParameterProvider* _this) {
    _this->updateParameters();
}

extern "C" __declspec(dllexport) const BaseType* Entity_getType(Entity* _this) {
    return &(_this->Type);
}

extern "C" __declspec(dllexport) wchar_t* Entity_getName(Entity* _this) {
    return copyStr(_this->getName().getData());
}

extern "C" __declspec(dllexport) void Entity_setName(Entity* _this, const wchar_t* name) {
    _this->setName(name);
}

/*extern "C" __declspec(dllexport) void Entity_setSelectable(Entity* _this, BOOL selectable) {
    return _this->setSelectable((bool)selectable);
}

extern "C" __declspec(dllexport) BOOL Entity_isSelectable(Entity* _this) {
    return _this->isSelectable();
}

extern "C" __declspec(dllexport) void Entity_setVisible(Entity* _this, BOOL visible) {
    return _this->setVisible((bool)visible);
}

extern "C" __declspec(dllexport) BOOL Entity_isVisible(Entity* _this) {
    return _this->isVisible();
}*/

extern "C" __declspec(dllexport) Entity* Entity_getParent(Entity* _this) {
    return _this->getParent();
}

extern "C" __declspec(dllexport) void Entity_setPropertyChangedListener(Entity* _this, listener_t listener) {
    _this->setOnChangedListener(listener);
}

extern "C" __declspec(dllexport) listener_t Entity_getPropertyChangedListener(Entity* _this) {
    return _this->getOnChangedListener();
}
