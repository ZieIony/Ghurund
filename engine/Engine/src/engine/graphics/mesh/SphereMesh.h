#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
    class SphereMesh: public MeshData {
    public:
        void init(unsigned int detail);
    };
}