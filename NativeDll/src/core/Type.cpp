#include "core/Type.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) const tchar *Type_getName(Type *_this) {
    return copyStr(_this->getName());
}
