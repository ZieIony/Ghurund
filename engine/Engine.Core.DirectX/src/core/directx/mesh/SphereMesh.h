#pragma once

#include "Mesh.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund {
    class SphereMesh: public Mesh {
    public:
        Status init(Graphics &graphics, CommandList &commandList, unsigned int detail = 2);
    };
}