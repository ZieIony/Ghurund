#include "core/Pointer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) unsigned int Pointer_getReferenceCount(Pointer *_this) {
    return _this->getReferenceCount();
}
