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
        mesh->init(context.Graphics, context.CommandList, 3);
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

    SelectionModel* Models::makeSelection(ResourceManager& resourceManager, ResourceContext& context) {
        ScopedPointer<Material> material = Materials::makeWireframe(resourceManager, context);

        ScopedPointer<Mesh> mesh = ghnew CubeMesh();
        mesh->init(context.Graphics, context.CommandList);
        SelectionModel* model = ghnew SelectionModel();
        model->Mesh = mesh;
        model->Material = material;
        model->initParameters(context.ParameterManager);
        model->Valid = true;

        model->initParameters(context.ParameterManager);
        model->Name = "selection";
        model->Valid = true;

        return model;
    }
}