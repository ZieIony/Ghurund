#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
    class CubeMeshData: public MeshData {
    public:
        void init(unsigned int detail = 0);
    };
}