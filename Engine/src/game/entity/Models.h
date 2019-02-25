#pragma once

#include "Model.h"
#include "graphics/mesh/PlaneMesh.h"
#include "graphics/mesh/QuadMesh.h"
#include "graphics/mesh/ConeMesh.h"
#include "graphics/shader/Shader.h"
#include "game/entity/TransformedEntity.h"

namespace Ghurund {
    class Models {
    private:
        Models() = delete;
        static TransformedEntity* makeTransformedEntity(ResourceContext& context, Mesh &mesh, Material& material);

    public:
        static TransformedEntity* makeCube(ResourceContext& context, Material& material);
        static TransformedEntity* makePlane(ResourceContext& context, Material& material);
        static TransformedEntity* makeSphere(ResourceContext& context, Material& material);
        static TransformedEntity* makeCone(ResourceContext& context, Material& material);
        static Model* makeQuad(ResourceContext& context, Material& material);
    };
}