#include "graphics/Materials.h"
#include "Models.h"

namespace Ghurund {
    Model* Models::makeCube(ResourceContext& context, Material& material) {
        Mesh* mesh = ghnew CubeMesh();
        mesh->init(context.Graphics, context.CommandList);
        Model *model = ghnew Model(mesh, &material);
        model->Valid = true;
        model->initParameters(context.ParameterManager);
        mesh->release();

        return model;
    }

    Model* Models::makePlane(ResourceContext& context, Material& material, unsigned int detail) {
        Mesh* mesh = ghnew PlaneMesh();
        mesh->init(context.Graphics, context.CommandList, detail);
        Model *model = ghnew Model(mesh, &material);
        model->Valid = true;
        model->initParameters(context.ParameterManager);
        mesh->release();

        return model;
    }

    Model* Models::makeSphere(ResourceContext& context, Material& material) {
        Mesh* mesh = ghnew SphereMesh();
        mesh->init(context.Graphics, context.CommandList);
        Model *model = ghnew Model(mesh, &material);
        model->Valid = true;
        model->initParameters(context.ParameterManager);
        mesh->release();

        return model;
    }

    Model* Models::makeCone(ResourceContext& context, Material& material) {
        Mesh* mesh = ghnew ConeMesh();
        mesh->init(context.Graphics, context.CommandList);
        Model *model = ghnew Model(mesh, &material);
        model->Valid = true;
        model->initParameters(context.ParameterManager);
        mesh->release();

        return model;
    }

    Model* Models::makeQuad(ResourceContext& context, Material& material) {
        Mesh* mesh = ghnew QuadMesh();
        mesh->init(context.Graphics, context.CommandList);

        Model* model = ghnew Model(mesh, &material);
        model->Valid = true;
        model->initParameters(context.ParameterManager);
        mesh->release();

        return model;
    }
}