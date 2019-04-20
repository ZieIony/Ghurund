#include "ThumbnailRenderer.h"

namespace Ghurund {
    const Ghurund::Type& ThumbnailRenderer::TYPE = Ghurund::Type([]() {return ghnew ThumbnailRenderer(); }, "ThumbnailRenderer");

    void ThumbnailRenderer::cameraLookAt(XMFLOAT3 center, XMFLOAT3 extents) {
        XMFLOAT3 pos;
        XMStoreFloat3(&pos, XMLoadFloat3(&center) + XMLoadFloat3(&extents) * 2);
        pos.z *= -1;
        camera->setPositionTargetUp(pos, center);
    }

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

    Status ThumbnailRenderer::render(Entity& entity, Image*& image) {
        cameraLookAt(entity.BoundingBox->Center, entity.BoundingBox->Extents);

        step->Entities.clear();
        step->Entities.add(&entity);
        renderer->render(*frame);
        frame->CommandList.wait();

        return renderTarget->capture(*resourceContext, image);
    }

    Status ThumbnailRenderer::render(Mesh& mesh, Image*& image) {
        Model* model = ghnew Model();
        model->Mesh = &mesh;
        model->Material = Materials::makeChecker(*resourceManager, *resourceContext);
        model->Valid = true;

        Status result = render(*model, image);

        model->release();

        return result;
    }

    Status ThumbnailRenderer::render(Material& material, Image*& image) {
        Model* model = Models::makeSphere(*resourceContext, material);

        BoundingOrientedBox boundingBox;
        XMFLOAT4X4 localTransformation = model->getTransformation();
        BoundingOrientedBox::CreateFromBoundingBox(boundingBox, *model->BoundingBox);
        boundingBox.Transform(boundingBox, XMLoadFloat4x4(&localTransformation));

        Status result = render(*model, image);

        model->release();

        return result;
    }
}