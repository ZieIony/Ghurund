#include "core/Pointer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) void Pointer_addReference(Pointer *_this) {
    _this->addReference();
}

extern "C" __declspec(dllexport) void Pointer_release(Pointer *_this) {
    _this->release();
}

extern "C" __declspec(dllexport) unsigned int Pointer_getReferenceCount(Pointer *_this) {
    return _this->getReferenceCount();
}
