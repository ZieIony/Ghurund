#pragma once

#include "Common.h"
#include "ui/gdi/Gdi.h"

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef _WIN64
#pragma comment(lib, "Ghurund.UI.GDI_64.lib")
#else
#pragma comment(lib, "Ghurund.UI.GDI_32.lib")
#endif

namespace Ghurund::UI::GDI {
    inline static const char* NAMESPACE_NAME = GH_STRINGIFY(Ghurund::UI::GDI);
}