#pragma once

#include "Model.h"
#include "graphics/mesh/PlaneMesh.h"
#include "graphics/shader/Shader.h"
#include "game/TransformedEntity.h"

namespace Ghurund {
    class Models {
    private:
        Models() = delete;

    public:
        static TransformedEntity *makeCube(ResourceContext &context, Material &material) {
            Mesh *mesh = ghnew CubeMesh();
            mesh->init(context.Graphics, context.CommandList);

            Model *model = ghnew Model(mesh, &material);
            model->Valid = true;
            TransformedEntity *entity = ghnew TransformedEntity(*model);
            model->initParameters(context.ParameterManager);
            mesh->release();
            model->release();

            return entity;
        }

        static TransformedEntity *makePlane(ResourceContext &context, Material &material) {
            Mesh *mesh = ghnew PlaneMesh();
            mesh->init(context.Graphics, context.CommandList);

            Model *model = ghnew Model(mesh, &material);
            model->Valid = true;
            TransformedEntity *entity = ghnew TransformedEntity(*model);
            model->initParameters(context.ParameterManager);
            mesh->release();
            model->release();

            return entity;
        }

        static TransformedEntity *makeSphere(ResourceContext &context, Material &material) {
            Mesh *mesh = ghnew SphereMesh();
            mesh->init(context.Graphics, context.CommandList);

            Model *model = ghnew Model(mesh, &material);
            model->Valid = true;
            TransformedEntity *entity = ghnew TransformedEntity(*model);
            model->initParameters(context.ParameterManager);
            mesh->release();
            model->release();

            return entity;
        }
    };
}