#pragma once

#include "graphics/mesh/Mesh.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund {
    class ConeMesh: public Mesh {
    protected:
        Status init(Graphics& graphics, CommandList& commandList, unsigned int detail = 2);
    };
}