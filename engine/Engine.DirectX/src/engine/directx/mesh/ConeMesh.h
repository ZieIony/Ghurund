#pragma once

#include "Mesh.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund {
    using namespace Ghurund::Engine::DirectX;

    class ConeMesh: public Mesh {
    public:
        void init(Graphics& graphics, CommandList& commandList, unsigned int detail = 2);
    };
}