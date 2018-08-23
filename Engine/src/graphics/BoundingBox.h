#pragma once

#include "Ghurund.h"

namespace Ghurund {
    class BoundingBox {
    private:
        XMFLOAT3 min = {}, max = {};

    public:
        void merge(BoundingBox &other) {
            min.x = std::min(min.x, other.min.x);
            min.y = std::min(min.y, other.min.y);
            min.z = std::min(min.z, other.min.z);
            max.x = std::max(max.x, other.max.x);
            max.y = std::max(max.y, other.max.y);
            max.z = std::max(max.z, other.max.z);
        }
    };
}