#include "collection/Array.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) size_t Array_Size(Array<void*> *_this) {
    return _this->Size;
}

extern "C" __declspec(dllexport) void *Array_get(Array<void*> *_this, size_t index) {
    return _this->get(index);
}

extern "C" __declspec(dllexport) void Array_set(Array<void*> *_this, size_t index, void *item) {
    _this->set(index, item);
}

extern "C" __declspec(dllexport) void Array_clear(Array<void*> *_this) {
    _this->clear();
}

extern "C" __declspec(dllexport) bool Array_contains(Array<void*> *_this, void *item) {
    return _this->contains(item);
}

extern "C" __declspec(dllexport) size_t Array_indexOf(Array<void*> *_this, void *item) {
    return _this->indexOf(item);
}
