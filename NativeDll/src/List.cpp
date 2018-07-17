#include "collection/List.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) size_t List_Size(List<void*> *_this) {
    return _this->Size;
}

extern "C" __declspec(dllexport) void List_add(List<void*> *_this, void *item) {
    _this->add(item);
}

extern "C" __declspec(dllexport) void List_insert(List<void*> *_this, size_t index, void *item) {
    _this->insertKeepOrder(index, item);
}

extern "C" __declspec(dllexport) bool List_remove(List<void*> *_this, void *item) {
    size_t index = _this->indexOf(item);
    if(index!=_this->Size) {
        _this->removeKeepOrder(item);
        return true;
    } else {
        return false;
    }
}

extern "C" __declspec(dllexport) void List_removeAt(List<void*> *_this, size_t index) {
    _this->removeAtKeepOrder(index);
}

extern "C" __declspec(dllexport) void *List_get(List<void*> *_this, size_t index) {
    return _this->get(index);
}

extern "C" __declspec(dllexport) void List_set(List<void*> *_this, size_t index, void *item) {
    _this->set(index, item);
}

extern "C" __declspec(dllexport) void List_clear(List<void*> *_this) {
    _this->clear();
}

extern "C" __declspec(dllexport) bool List_contains(List<void*> *_this, void *item) {
    return _this->contains(item);
}

extern "C" __declspec(dllexport) size_t List_indexOf(List<void*> *_this, void *item) {
    return _this->indexOf(item);
}
