#pragma once

namespace Ghurund {
    struct Matrix3x2 {
        union {
            struct {
                float m11, m12, m21, m22, dx, dy;
            };

            float m[3][2];
        };

    };
}
