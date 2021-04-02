#pragma once

#include "DrawableComponent.h"
#include "graphics/mesh/PlaneMesh.h"
#include "graphics/mesh/QuadMesh.h"
#include "graphics/mesh/ConeMesh.h"
#include "graphics/shader/Shader.h"

namespace Ghurund {
    class DrawableComponents {
    private:
        DrawableComponents() = delete;

    public:
        static DrawableComponent* makeCube(ResourceContext& context, Material& material);
        static DrawableComponent* makePlane(ResourceContext& context, Material& material, unsigned int detail = 1);
        static DrawableComponent* makeSphere(ResourceContext& context, Material& material);
        static DrawableComponent* makeCone(ResourceContext& context, Material& material);
        static DrawableComponent* makeQuad(ResourceContext& context, Material& material);
    };
}