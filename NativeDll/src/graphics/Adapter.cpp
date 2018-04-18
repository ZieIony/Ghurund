#include "graphics/Adapter.h"

using namespace Ghurund;
using namespace std;

extern "C" __declspec(dllexport) tchar *Adapter_getName(Adapter *_this) {
    return copyStr(_this->getName().getData());
}

extern "C" __declspec(dllexport) unsigned int Adapter_getDedicatedVideoMemory(Adapter *_this) {
    return _this->getDedicatedVideoMemory();
}

extern "C" __declspec(dllexport) size_t Adapter_getOutputs_Size(Adapter *_this) {
    return _this->getOutputs().Size;
}

extern "C" __declspec(dllexport) AdapterOutput *Adapter_getOutputs_get(Adapter *_this, size_t index) {
    return _this->getOutputs().get(index);
}


extern "C" __declspec(dllexport) tchar *AdapterOutput_getName(AdapterOutput *_this) {
    return copyStr(_this->getName().getData());
}

extern "C" __declspec(dllexport) size_t AdapterOutput_getDisplayModes_Size(AdapterOutput *_this) {
    return _this->getDisplayModes().Size;
}

extern "C" __declspec(dllexport) DisplayMode *AdapterOutput_getDisplayModes_get(AdapterOutput *_this, size_t index) {
    return _this->getDisplayModes().get(index);
}


extern "C" __declspec(dllexport) unsigned int DisplayMode_getWidth(DisplayMode *_this) {
    return _this->getWidth();
}

extern "C" __declspec(dllexport) unsigned int DisplayMode_getHeight(DisplayMode *_this) {
    return _this->getHeight();
}

extern "C" __declspec(dllexport) float DisplayMode_getRefreshRate(DisplayMode *_this) {
    return _this->getRefreshRate();
}
