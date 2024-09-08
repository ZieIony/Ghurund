#pragma once

#include "Ghurund.UI.h"
#include "Ghurund.Engine.DirectX.h"

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

namespace Ghurund::UI::Direct2D {
    inline static const char* NAMESPACE_NAME = GH_STRINGIFY(Ghurund::UI::Direct2D);
}