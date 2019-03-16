#include "graphics/Graphics.h"

using namespace Ghurund;
using namespace std;

extern "C" __declspec(dllexport) Graphics *Graphics_new() {
    return new Graphics();
}

extern "C" __declspec(dllexport) Status Graphics_init(Graphics *graphics) {
    return graphics->init();
}

extern "C" __declspec(dllexport) size_t Graphics_getAdapters_Size(Graphics *graphics) {
    return graphics->getAdapters().Size;
}

extern "C" __declspec(dllexport) Adapter *Graphics_getAdapters_get(Graphics *graphics, size_t i) {
    return graphics->getAdapters().get(i);
}

#include "Ghurund.h"
#include "Dxgi1_6.h"
#include <dxgidebug.h>

using namespace Ghurund;
using namespace DirectX;

extern "C" __declspec(dllexport) void reportLiveObjects() {
    ComPtr<IDXGIDebug> debugInterface;
    if(SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debugInterface))))
        debugInterface->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
}
