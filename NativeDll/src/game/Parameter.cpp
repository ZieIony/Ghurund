#include "game/parameter/Parameter.h"

#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) const ParameterTypeValue Parameter_getType(Parameter *_this) {
    return _this->Type.Value;
}

extern "C" __declspec(dllexport) float Parameter_getFloatValue(Parameter *_this) {
    return *(float*)(_this->getValue());
}

extern "C" __declspec(dllexport) Float2 Parameter_getFloat2Value(Parameter *_this) {
    return convertFloat2(*(XMFLOAT2*)_this->getValue());
}

extern "C" __declspec(dllexport) Float3 Parameter_getFloat3Value(Parameter *_this) {
    return convertFloat3(*(XMFLOAT3*)_this->getValue());
}

extern "C" __declspec(dllexport) Matrix Parameter_getMatrixValue(Parameter *_this) {
    return convertMatrix(*(XMFLOAT4X4*)_this->getValue());
}

extern "C" __declspec(dllexport) void Parameter_setValue(Parameter *_this, const void *value) {
    _this->setValue(value);
}

extern "C" __declspec(dllexport) tchar *Parameter_getName(Parameter *_this) {
    return toTchar(_this->getName().getData());
}
