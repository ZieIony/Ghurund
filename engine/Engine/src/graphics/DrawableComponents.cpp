#include "ghpch.h"

#include "DrawableComponents.h"

#include "graphics/Materials.h"
#include "core/IntrusivePointer.h"
#include "core/directx/mesh/CubeMesh.h"
#include "core/directx/mesh/SphereMesh.h"

namespace Ghurund {
    DrawableComponent* DrawableComponents::makeCube(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeIntrusive<CubeMesh>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh.get();
		model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makePlane(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material, unsigned int detail) {
        auto mesh = makeIntrusive<PlaneMesh>();
        mesh->init(graphics, commandList);
		DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh.get();
		model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeSphere(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeIntrusive<SphereMesh>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeCone(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeIntrusive<ConeMesh>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeQuad(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeIntrusive<QuadMesh>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }
}