#pragma once

#include "VertexStream.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine {
    using namespace ::DirectX;

    class MeshProcessor {
    private:
        MeshProcessor() = delete;

    public:
        static DirectX::BoundingBox computeBoundingBox(const VertexStream& positionStream);
    };
}
