#include "graphics/Materials.h"
#include "Models.h"
#include "core/ScopedPointer.h"

namespace Ghurund {
    Model* Models::makeCube(ResourceContext& context, Material& material) {
        ScopedPointer<Mesh> mesh = ghnew CubeMesh();
        mesh->init(context.Graphics, context.CommandList);
        Model* model = ghnew Model(mesh, &material);
        model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    Model* Models::makePlane(ResourceContext& context, Material& material, unsigned int detail) {
        ScopedPointer<Mesh> mesh = ghnew PlaneMesh();
        mesh->init(context.Graphics, context.CommandList, detail);
        Model* model = ghnew Model(mesh, &material);
        model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    Model* Models::makeSphere(ResourceContext& context, Material& material, const PxMaterial* properties) {
        PxShape* shape = nullptr;
        if (properties)
            shape = context.Physics.get().createShape(PxSphereGeometry(1), *properties);

        ScopedPointer<Mesh> mesh = ghnew SphereMesh();
        mesh->init(context.Graphics, context.CommandList);
        Model* model = ghnew Model(mesh, &material, shape);
        model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    Model* Models::makeCone(ResourceContext& context, Material& material) {
        ScopedPointer<Mesh> mesh = ghnew ConeMesh();
        mesh->init(context.Graphics, context.CommandList);
        Model* model = ghnew Model(mesh, &material);
        model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    Model* Models::makeQuad(ResourceContext& context, Material& material) {
        ScopedPointer<Mesh> mesh = ghnew QuadMesh();
        mesh->init(context.Graphics, context.CommandList);

        Model* model = ghnew Model(mesh, &material);
        model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    Model* Models::makeSelection(ResourceManager& resourceManager, ResourceContext& context, Model& model) {
        ScopedPointer<Material> material = Materials::makeWireframe(resourceManager, context);
        Model* selection = Models::makeCube(context, *material);
        selection->initParameters(context.ParameterManager);
        selection->Name = "selection";
        selection->Valid = true;

        selection->Position = model.Mesh->BoundingBox.Center;
        selection->Scale = model.Mesh->BoundingBox.Extents;

        return selection;
    }
}