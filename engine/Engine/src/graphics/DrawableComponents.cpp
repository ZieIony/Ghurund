#include "ghpch.h"

#include "DrawableComponents.h"

#include "graphics/Materials.h"
#include "core/SharedPointer.h"
#include "graphics/mesh/CubeMesh.h"
#include "graphics/mesh/SphereMesh.h"

namespace Ghurund {
    DrawableComponent* DrawableComponents::makeCube(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeShared<CubeMesh>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh.get();
		model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makePlane(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material, unsigned int detail) {
        auto mesh = makeShared<PlaneMesh>();
        mesh->init(graphics, commandList);
		DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh.get();
		model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeSphere(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeShared<SphereMesh>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeCone(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeShared<ConeMesh>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeQuad(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeShared<QuadMesh>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }
}