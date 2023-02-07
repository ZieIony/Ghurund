#pragma once

#include "Mesh.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund {
    using namespace Ghurund::Core::DirectX;

    class ConeMesh: public Mesh {
    public:
        Status init(Graphics& graphics, CommandList& commandList, unsigned int detail = 2);
    };
}