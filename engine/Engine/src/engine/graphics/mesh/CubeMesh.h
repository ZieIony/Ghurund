#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
    class CubeMesh: public MeshData {
    public:
        void init(unsigned int detail = 0);
    };
}