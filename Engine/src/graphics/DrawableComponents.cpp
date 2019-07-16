#include "graphics/Materials.h"
#include "DrawableComponents.h"
#include "core/ScopedPointer.h"
#include "graphics/mesh/CubeMesh.h"
#include "graphics/mesh/SphereMesh.h"

namespace Ghurund {
    DrawableComponent* DrawableComponents::makeCube(ResourceContext& context, Material& material) {
        ScopedPointer<Mesh> mesh = ghnew CubeMesh();
        mesh->init(context.Graphics, context.CommandList);
        DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh;
		model->Material = &material;
        model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    DrawableComponent* DrawableComponents::makePlane(ResourceContext& context, Material& material, unsigned int detail) {
        ScopedPointer<Mesh> mesh = ghnew PlaneMesh();
        mesh->init(context.Graphics, context.CommandList, detail);
		DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh;
		model->Material = &material;
		model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    DrawableComponent* DrawableComponents::makeSphere(ResourceContext& context, Material& material) {
        ScopedPointer<Mesh> mesh = ghnew SphereMesh();
        mesh->init(context.Graphics, context.CommandList, 3);
		DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh;
		model->Material = &material;
		model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    DrawableComponent* DrawableComponents::makeCone(ResourceContext& context, Material& material) {
        ScopedPointer<Mesh> mesh = ghnew ConeMesh();
        mesh->init(context.Graphics, context.CommandList);
		DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh;
		model->Material = &material;
		model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }

    DrawableComponent* DrawableComponents::makeQuad(ResourceContext& context, Material& material) {
        ScopedPointer<Mesh> mesh = ghnew QuadMesh();
        mesh->init(context.Graphics, context.CommandList);
		DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh;
		model->Material = &material;
		model->initParameters(context.ParameterManager);
        model->Valid = true;

        return model;
    }
}