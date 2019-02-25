#include "graphics/Materials.h"
#include "Models.h"

namespace Ghurund {
    TransformedEntity* Models::makeTransformedEntity(ResourceContext& context, Mesh& mesh, Material& material) {
        Model* model = ghnew Model(&mesh, &material);
        model->Valid = true;
        TransformedEntity* entity = ghnew TransformedEntity(*model);
        entity->Valid = true;
        model->initParameters(context.ParameterManager);
        model->release();

        return entity;
    }

    TransformedEntity* Models::makeCube(ResourceContext& context, Material& material) {
        Mesh* mesh = ghnew CubeMesh();
        mesh->init(context.Graphics, context.CommandList);
        TransformedEntity* entity = makeTransformedEntity(context, *mesh, material);
        mesh->release();

        return entity;
    }

    TransformedEntity* Models::makePlane(ResourceContext& context, Material& material) {
        Mesh* mesh = ghnew PlaneMesh();
        mesh->init(context.Graphics, context.CommandList);
        TransformedEntity* entity = makeTransformedEntity(context, *mesh, material);
        mesh->release();

        return entity;
    }

    TransformedEntity* Models::makeSphere(ResourceContext& context, Material& material) {
        Mesh* mesh = ghnew SphereMesh();
        mesh->init(context.Graphics, context.CommandList);
        TransformedEntity* entity = makeTransformedEntity(context, *mesh, material);
        mesh->release();

        return entity;
    }

    TransformedEntity* Models::makeCone(ResourceContext& context, Material& material) {
        Mesh* mesh = ghnew ConeMesh();
        mesh->init(context.Graphics, context.CommandList);
        TransformedEntity* entity = makeTransformedEntity(context, *mesh, material);
        mesh->release();

        return entity;
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