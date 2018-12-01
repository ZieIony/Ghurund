#pragma once

#include "Model.h"
#include "graphics/mesh/PlaneMesh.h"
#include "graphics/shader/Shader.h"
#include "game/entity/TransformedEntity.h"

namespace Ghurund {
    class Models {
    private:
        Models() = delete;

    public:
        static TransformedEntity *makeCube(ResourceContext &context, Material &material);
        static TransformedEntity *makePlane(ResourceContext &context, Material &material);
        static TransformedEntity *makeSphere(ResourceContext &context, Material &material);
    };
}