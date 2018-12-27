#include "collection/PointerList.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) size_t PointerList_Size(PointerList<Pointer*> *_this) {
    return _this->Size;
}

extern "C" __declspec(dllexport) void PointerList_add(PointerList<Pointer*> *_this, Pointer *item) {
    _this->add(item);
}

extern "C" __declspec(dllexport) void PointerList_insert(PointerList<Pointer*> *_this, size_t index, Pointer *item) {
    _this->insertKeepOrder(index, item);
}

extern "C" __declspec(dllexport) bool PointerList_remove(PointerList<Pointer*> *_this, Pointer *item) {
    size_t index = _this->indexOf(item);
    if(index!=_this->Size) {
        _this->removeKeepOrder(item);
        return true;
    } else {
        return false;
    }
}

extern "C" __declspec(dllexport) void PointerList_removeAt(PointerList<Pointer*> *_this, size_t index) {
    _this->removeAtKeepOrder(index);
}

extern "C" __declspec(dllexport) void *PointerList_get(PointerList<Pointer*> *_this, size_t index) {
    return _this->get(index);
}

extern "C" __declspec(dllexport) void PointerList_set(PointerList<Pointer*> *_this, size_t index, Pointer *item) {
    _this->set(index, item);
}

extern "C" __declspec(dllexport) void PointerList_clear(PointerList<Pointer*> *_this) {
    _this->clear();
}

extern "C" __declspec(dllexport) bool PointerList_contains(PointerList<Pointer*> *_this, Pointer *item) {
    return _this->contains(item);
}

extern "C" __declspec(dllexport) size_t PointerList_indexOf(PointerList<Pointer*> *_this, Pointer *item) {
    return _this->indexOf(item);
}
