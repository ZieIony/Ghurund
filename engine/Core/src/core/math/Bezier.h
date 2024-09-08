#pragma once

#include "Point.h"

namespace Ghurund::Core {
    struct BezierQuadratic {
        FloatPoint start, control, end;
    };

    struct BezierCubic {
        FloatPoint start, control0, control1, end;

        static BezierCubic fromQuadratic(FloatPoint start, FloatPoint control, FloatPoint end) {
            FloatPoint c0 = {
                start.x + 2 * (control.x - start.x) / 3,
                start.y + 2 * (control.y - start.y) / 3
            };

            FloatPoint c1 = {
                control.x + 1 * (end.x - control.x) / 3,
                control.y + 1 * (end.y - control.y) / 3
            };

            return { start, c0, c1, end };
        }
    };
}