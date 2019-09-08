#pragma once

#include "Common.h"
#include <DirectXMath.h>

namespace Ghurund {
    using namespace DirectX;

    inline XMFLOAT4 makeColor(unsigned int color) {
        unsigned int a = (color >> 24) & 0xff;
        unsigned int r = (color >> 16) & 0xff;
        unsigned int g = (color >> 8) & 0xff;
        unsigned int b = color & 0xff;
        return XMFLOAT4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    template<class Type> inline Type minMax(Type a, Type b, Type c) {
        if (b < a)
            return a;
        if (b > c)
            return c;
        return b;
    }

    template<class Type> inline Type lerp(Type val1, Type val2, float fact) {
        return (1 - fact) * val1 + fact * val2;
    }

    template<class Type> inline Type round(Type a) {
        return floor(a + (Type)0.5);
    }

    template<class Type> inline Type frac(Type a) {
        float a2 = abs(a);
        return a2 - floor(a2);
    }

    inline float random() {
        return (float)rand() / (float)RAND_MAX;
    }

    enum class VectorComponent {
        X, Y, Z, W
    };

    inline uint32_t swizzle(uint32_t val, VectorComponent x, VectorComponent y, VectorComponent z, VectorComponent w) {
        uint32_t data[4];
        data[0] = val >> 24;
        data[1] = (val >> 16) & 0xff;
        data[2] = (val >> 8) & 0xff;
        data[3] = val & 0xff;
        return (data[(unsigned int)x] << 24) | (data[(unsigned int)y] << 16) | (data[(unsigned int)z] << 8) | data[(unsigned int)w];
    }

	constexpr unsigned long long operator"" _KB(unsigned long long val) {
		return val * 1024;
	}

	constexpr unsigned long long operator"" _MB(unsigned long long val) {
		return val * 1024 * 1024;
	}
}