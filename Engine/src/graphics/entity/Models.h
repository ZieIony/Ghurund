#pragma once

#include "Model.h"
#include "graphics/mesh/PlaneMesh.h"
#include "graphics/mesh/QuadMesh.h"
#include "graphics/mesh/ConeMesh.h"
#include "graphics/shader/Shader.h"

#include <PxMaterial.h>

namespace Ghurund {
    using namespace physx;

    class Models {
    private:
        Models() = delete;

    public:
        static Model* makeCube(ResourceContext& context, Material& material);
        static Model* makePlane(ResourceContext& context, Material& material, unsigned int detail = 1);
        static Model* makeSphere(ResourceContext& context, Material& material, const PxMaterial* properties = nullptr);
        static Model* makeCone(ResourceContext& context, Material& material);
        static Model* makeQuad(ResourceContext& context, Material& material);
    };
}