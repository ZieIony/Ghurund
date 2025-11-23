#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
    class ConeMeshData: public MeshData {
    public:
        void init(unsigned int detail = 2);
    };
}