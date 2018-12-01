#include "Models.h"

namespace Ghurund {
    TransformedEntity * Models::makeCube(ResourceContext & context, Material & material) {
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

    TransformedEntity * Models::makePlane(ResourceContext & context, Material & material) {
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

    TransformedEntity * Models::makeSphere(ResourceContext & context, Material & material) {
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
}