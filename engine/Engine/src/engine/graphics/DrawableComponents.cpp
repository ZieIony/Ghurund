#include "ghepch.h"

#include "DrawableComponents.h"

/*#include "graphics/Materials.h"
#include "core/object/IntrusivePointer.h"
#include "core/directx/mesh/CubeMeshData.h"
#include "core/directx/mesh/SphereMeshData.h"*/

namespace Ghurund::Engine {
    /*DrawableComponent* DrawableComponents::makeCube(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeIntrusive<CubeMeshData>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh.get();
		model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makePlane(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material, unsigned int detail) {
        auto mesh = makeIntrusive<PlaneMeshData>();
        mesh->init(graphics, commandList);
		DrawableComponent* model = ghnew DrawableComponent();
		model->Mesh = mesh.get();
		model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeSphere(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeIntrusive<SphereMeshData>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeCone(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeIntrusive<ConeMeshData>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }

    DrawableComponent* DrawableComponents::makeQuad(Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager, Material& material) {
        auto mesh = makeIntrusive<QuadMeshData>();
        mesh->init(graphics, commandList);
        DrawableComponent* model = ghnew DrawableComponent();
        model->Mesh = mesh.get();
        model->Material = &material;
        //model->initParameters(parameterManager);

        return model;
    }*/
}