#pragma once

#include "core/collection/Map.h"
#include "core/math/Size.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
    using namespace Ghurund::Core;
    using namespace ::DirectX;

    struct GlyphMetrics {
        IntSize shapeSize, bitmapSize;
        XMINT2 shapeOrigin, bitmapPos;
        float scale;
        uint16_t increment;
    };
}