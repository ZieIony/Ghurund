#pragma once

#include "Common.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace Ghurund {
    template<class Type> inline Type minMax(Type a, Type b, Type c) {
        if(b < a)
            return a;
        if(b > c)
            return c;
        return b;
    }

    template<class Type> inline Type lerp(Type val1, Type val2, float fact) {
        return (1 - fact)*val1 + fact*val2;
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
}