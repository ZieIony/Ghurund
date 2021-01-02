#include "Window.h"

#include <DirectXMath.h>

namespace Ghurund {
    using namespace DirectX;

    void Window::updateParameters() {
        XMFLOAT2 sizeParam = { (float)size.width, (float)size.height };
        parameterViewportSize->setValue(&sizeParam);
    }
}