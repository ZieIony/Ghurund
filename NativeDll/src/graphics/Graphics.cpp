#include "graphics/Graphics.h"

using namespace Ghurund;
using namespace std;

extern "C" __declspec(dllexport) Graphics *Graphics_new() {
    return new Graphics();
}

extern "C" __declspec(dllexport) void Graphics_init(Graphics *graphics) {
    graphics->init();
}

extern "C" __declspec(dllexport) size_t Graphics_getAdapters_Size(Graphics *graphics) {
    return graphics->getAdapters().Size;
}

extern "C" __declspec(dllexport) Adapter *Graphics_getAdapters_get(Graphics *graphics, size_t i) {
    return graphics->getAdapters().get(i);
}
