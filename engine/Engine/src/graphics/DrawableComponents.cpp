#include "ghpch.h"
#include "DrawableComponents.h"

#include "graphics/Materials.h"
#include "core/SharedPointer.h"
#include "graphics/mesh/CubeMesh.h"
#include "graphics/mesh/SphereMesh.h"

namespace Ghurund {
    DrawableComponent* DrawableComponents::makeCube(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        SharedPointer<Mesh> mesh = ghnew CubeMesh();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh;
		model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makePlane(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material, unsigned int detail) {
        SharedPointer<Mesh> mesh = ghnew PlaneMesh();
        mesh->init(graphics, commandList);
		DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh;
		model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeSphere(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        SharedPointer<Mesh> mesh = ghnew SphereMesh();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh;
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeCone(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        SharedPointer<Mesh> mesh = ghnew ConeMesh();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh;
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeQuad(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        SharedPointer<Mesh> mesh = ghnew QuadMesh();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh;
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }
}