#include "editor/ObservableObject.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) void ObservableObject_setOnChangedListener(ObservableObject *_this, void(__stdcall *listener)()) {
    _this->setOnChangedListener(listener);
}
