#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
    class SphereMeshData: public MeshData {
    public:
        void init(unsigned int detail);
    };
}