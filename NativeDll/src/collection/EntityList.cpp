#include "game/entity/EntityList.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) size_t EntityList_Size(EntityList *_this) {
    return _this->Size;
}

extern "C" __declspec(dllexport) void EntityList_add(EntityList *_this, Entity *item) {
    _this->add(item);
}

extern "C" __declspec(dllexport) void EntityList_insert(EntityList *_this, size_t index, Entity *item) {
    _this->insertKeepOrder(index, item);
}

extern "C" __declspec(dllexport) bool EntityList_remove(EntityList *_this, Entity *item) {
    size_t index = _this->indexOf(item);
    if(index!=_this->Size) {
        _this->removeKeepOrder(item);
        return true;
    } else {
        return false;
    }
}

extern "C" __declspec(dllexport) void EntityList_removeAt(EntityList *_this, size_t index) {
    _this->removeAtKeepOrder(index);
}

extern "C" __declspec(dllexport) void *EntityList_get(EntityList *_this, size_t index) {
    return _this->get(index);
}

extern "C" __declspec(dllexport) void EntityList_set(EntityList *_this, size_t index, Entity *item) {
    _this->set(index, item);
}

extern "C" __declspec(dllexport) void EntityList_clear(EntityList *_this) {
    _this->clear();
}

extern "C" __declspec(dllexport) bool EntityList_contains(EntityList *_this, Entity *item) {
    return _this->contains(item);
}

extern "C" __declspec(dllexport) size_t EntityList_indexOf(EntityList *_this, Entity *item) {
    return _this->indexOf(item);
}
