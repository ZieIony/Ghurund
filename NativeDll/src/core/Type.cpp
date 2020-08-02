#include "core/reflection/Type.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) void Type_delete(Type *_this) {
    delete _this;
}

extern "C" __declspec(dllexport) const char *Type_getName(Type *_this) {
    return copyStr(_this->getName());
}
