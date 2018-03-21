#include "graphics/Graphics.h"

using namespace Ghurund;
using namespace std;

extern "C" __declspec(dllexport) Graphics *Graphics_new() {
    return new Graphics();
}

extern "C" __declspec(dllexport) void Graphics_init(Graphics *graphics) {
    graphics->init();
}
