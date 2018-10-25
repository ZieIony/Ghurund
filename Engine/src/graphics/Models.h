#pragma once

#include "Model.h"
#include "graphics/mesh/PlaneMesh.h"
#include "graphics/shader/Shader.h"

namespace Ghurund {
    class Models {
    private:
        Models() = delete;

    public:
        static TransformedEntity *makePlane(ResourceContext &context, Material &material) {
            PlaneMesh *mesh = ghnew PlaneMesh();
            mesh->init(context.Graphics, context.CommandList);

            Model *model = ghnew Model(mesh, &material);
            TransformedEntity *entity = ghnew TransformedEntity(*model);
            model->initParameters(context.ParameterManager);
            mesh->release();

            return entity;
        }
    };
}