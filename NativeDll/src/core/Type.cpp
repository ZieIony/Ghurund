#include "core/Type.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) void Type_delete(BaseType *_this) {
    delete _this;
}

extern "C" __declspec(dllexport) const char *Type_getName(BaseType *_this) {
    return copyStr(_this->getName());
}
