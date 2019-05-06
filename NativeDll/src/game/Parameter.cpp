#include "game/parameter/ValueParameter.h"
#include "game/parameter/ResourceParameter.h"

#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) const ParameterValueTypeValue Parameter_getType(Parameter *_this) {
    return _this->ValueType.Value;
}


extern "C" __declspec(dllexport) int ValueParameter_getIntValue(ValueParameter *_this) {
    return *(int*)(_this->getValue());
}

extern "C" __declspec(dllexport) Int2 ValueParameter_getInt2Value(ValueParameter *_this) {
    return convertInt2(*(XMINT2*)(_this->getValue()));
}

extern "C" __declspec(dllexport) float ValueParameter_getFloatValue(ValueParameter *_this) {
    return *(float*)(_this->getValue());
}

extern "C" __declspec(dllexport) Float2 ValueParameter_getFloat2Value(ValueParameter *_this) {
    return convertFloat2(*(XMFLOAT2*)_this->getValue());
}

extern "C" __declspec(dllexport) Float3 ValueParameter_getFloat3Value(ValueParameter *_this) {
    return convertFloat3(*(XMFLOAT3*)_this->getValue());
}

extern "C" __declspec(dllexport) Matrix ValueParameter_getMatrixValue(ValueParameter *_this) {
    return convertMatrix(*(XMFLOAT4X4*)_this->getValue());
}

extern "C" __declspec(dllexport) Float4 ValueParameter_getColorValue(ValueParameter *_this) {
    return convertFloat4(*(XMFLOAT4*)_this->getValue());
}

extern "C" __declspec(dllexport) Resource *ResourceParameter_getValue(ResourceParameter *_this) {
    return _this->getValue();
}


extern "C" __declspec(dllexport) void ValueParameter_setIntValue(ValueParameter *_this, int value) {
    _this->setValue(&value);
}

extern "C" __declspec(dllexport) void ValueParameter_setInt2Value(ValueParameter *_this, Int2 value) {
    _this->setValue(&convertInt2(value));
}

extern "C" __declspec(dllexport) void ValueParameter_setFloatValue(ValueParameter *_this, float value) {
    _this->setValue(&value);
}

extern "C" __declspec(dllexport) void ValueParameter_setFloat2Value(ValueParameter *_this, Float2 value) {
    _this->setValue(&convertFloat2(value));
}

extern "C" __declspec(dllexport) void ValueParameter_setFloat3Value(ValueParameter *_this, Float3 value) {
    _this->setValue(&convertFloat3(value));
}

extern "C" __declspec(dllexport) void ValueParameter_setMatrixValue(ValueParameter *_this, Matrix value) {
    _this->setValue(&convertMatrix(value));
}

extern "C" __declspec(dllexport) void ValueParameter_setColorValue(ValueParameter *_this, Float4 value) {
    _this->setValue(&convertFloat4(value));
}

extern "C" __declspec(dllexport) void ResourceParameter_setValue(ResourceParameter *_this, Resource *value) {
    _this->setValue(value);
}


extern "C" __declspec(dllexport) tchar *Parameter_getName(Parameter *_this) {
    return toTchar(_this->getName().getData());
}
