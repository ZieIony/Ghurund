#pragma once

namespace Ghurund::Core {
    struct Matrix3x2 {
        union {
            struct {
                float m11, m12, m21, m22, dx, dy;
            };

            float m[3][2];
        };

        virtual bool operator==(const Matrix3x2& other) const {
            return memcmp(m, other.m, sizeof(float) * 6) == 0;
        }
    };
}
