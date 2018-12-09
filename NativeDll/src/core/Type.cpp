#include "core/Type.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) void Type_delete(Type *_this) {
    delete _this;
}

extern "C" __declspec(dllexport) const tchar *Type_getName(Type *_this) {
    return copyStr(_this->getName());
}
