#pragma once

#include "Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class CubeMesh: public Mesh {
    public:
        Status init(Graphics& graphics, CommandList& commandList, unsigned int detail = 0);
    };
}