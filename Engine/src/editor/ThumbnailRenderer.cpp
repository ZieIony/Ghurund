#include "ThumbnailRenderer.h"

namespace Ghurund {
    const Ghurund::Type& ThumbnailRenderer::TYPE = Ghurund::Type([]() {return ghnew ThumbnailRenderer(); }, "ThumbnailRenderer");
 
    void ThumbnailRenderer::init(ResourceManager& resourceManager, ResourceContext& context, UINT32 width, UINT32 height) {
        this->resourceManager = &resourceManager;
        this->resourceContext = &context;

        camera = ghnew Camera();
        camera->initParameters(context.ParameterManager);
        camera->setScreenSize(width, height);

        step = ghnew RenderStep();
        step->initParameters(context.ParameterManager);
        step->Camera = camera;

        renderer = ghnew Renderer();
        XMFLOAT4 color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1);
        renderer->ClearColor = &color;
        renderer->Steps.add(step);

        renderTarget = ghnew RenderTarget();
        renderTarget->init(context.Graphics, width, height, DXGI_FORMAT_R8G8B8A8_UNORM);
        depthBuffer = ghnew DepthBuffer();
        depthBuffer->init(context.Graphics, width, height);

        frame = ghnew Frame();
        D3D12_VIEWPORT viewport = D3D12_VIEWPORT{0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height),0,1};
        D3D12_RECT scissorRect = D3D12_RECT{0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
        frame->init(context.Graphics, viewport, scissorRect, renderTarget, depthBuffer);

        renderer->init(resourceManager, context);
    }

    void ThumbnailRenderer::render(Model& model, Image*& image) {
        Mesh* mesh = model.Mesh;
        XMFLOAT3 pos;
        XMStoreFloat3(&pos, XMLoadFloat3(&mesh->BoundingBox.Center) + XMLoadFloat3(&mesh->BoundingBox.Extents) * 2);
        pos.z *= -1;
        camera->setPositionTargetUp(pos, mesh->BoundingBox.Center);
        mesh->release();

        step->Entities.clear();
        step->Entities.add(&model);
        renderer->render(*frame);
        frame->CommandList.wait();

        renderTarget->capture(*resourceContext, image);
    }

    void ThumbnailRenderer::render(Mesh& mesh, Image*& image) {
        XMFLOAT3 pos;
        XMStoreFloat3(&pos, XMLoadFloat3(&mesh.BoundingBox.Center) + XMLoadFloat3(&mesh.BoundingBox.Extents) * 2);
        pos.z *= -1;
        camera->setPositionTargetUp(pos, mesh.BoundingBox.Center);

        Model* model = ghnew Model();
        model->Mesh = &mesh;
        model->Material = Materials::makeChecker(*resourceManager, *resourceContext);
        model->Valid = true;

        step->Entities.clear();
        step->Entities.add(model);
        renderer->render(*frame);
        frame->CommandList.wait();

        model->release();

        renderTarget->capture(*resourceContext, image);
    }

}