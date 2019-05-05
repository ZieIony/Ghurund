#include "game/parameter/Parameter.h"

#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) const ParameterValueTypeValue Parameter_getType(Parameter *_this) {
    return _this->Type.Value;
}


extern "C" __declspec(dllexport) int Parameter_getIntValue(Parameter *_this) {
    return *(int*)(_this->getValue());
}

extern "C" __declspec(dllexport) Int2 Parameter_getInt2Value(Parameter *_this) {
    return convertInt2(*(XMINT2*)(_this->getValue()));
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

extern "C" __declspec(dllexport) Float4 Parameter_getColorValue(Parameter *_this) {
    return convertFloat4(*(XMFLOAT4*)_this->getValue());
}


extern "C" __declspec(dllexport) void Parameter_setIntValue(Parameter *_this, int value) {
    _this->setValue(&value);
}

extern "C" __declspec(dllexport) void Parameter_setInt2Value(Parameter *_this, Int2 value) {
    _this->setValue(&convertInt2(value));
}

extern "C" __declspec(dllexport) void Parameter_setFloatValue(Parameter *_this, float value) {
    _this->setValue(&value);
}

extern "C" __declspec(dllexport) void Parameter_setFloat2Value(Parameter *_this, Float2 value) {
    _this->setValue(&convertFloat2(value));
}

extern "C" __declspec(dllexport) void Parameter_setFloat3Value(Parameter *_this, Float3 value) {
    _this->setValue(&convertFloat3(value));
}

extern "C" __declspec(dllexport) void Parameter_setMatrixValue(Parameter *_this, Matrix value) {
    _this->setValue(&convertMatrix(value));
}

extern "C" __declspec(dllexport) void Parameter_setColorValue(Parameter *_this, Float4 value) {
    _this->setValue(&convertFloat4(value));
}


extern "C" __declspec(dllexport) void Parameter_setValue(Parameter *_this, const void *value) {
    _this->setValue(value);
}


extern "C" __declspec(dllexport) tchar *Parameter_getName(Parameter *_this) {
    return toTchar(_this->getName().getData());
}
