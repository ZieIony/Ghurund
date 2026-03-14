#pragma once

#include "Point.h"

namespace Ghurund::Core {
    struct BezierQuadratic {
        XMFLOAT2 start, control, end;
    };

    struct BezierCubic {
        XMFLOAT2 start, control0, control1, end;

        static BezierCubic fromQuadratic(XMFLOAT2 start, XMFLOAT2 control, XMFLOAT2 end) {
            XMFLOAT2 c0 = {
                start.x + 2 * (control.x - start.x) / 3,
                start.y + 2 * (control.y - start.y) / 3
            };

            XMFLOAT2 c1 = {
                control.x + 1 * (end.x - control.x) / 3,
                control.y + 1 * (end.y - control.y) / 3
            };

            return { start, c0, c1, end };
        }
    };
}
