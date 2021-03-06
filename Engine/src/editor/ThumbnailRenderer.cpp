#include "ghpch.h"
#include "ThumbnailRenderer.h"

#include "CameraUtils.h"

namespace Ghurund {
    const Ghurund::Type& ThumbnailRenderer::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<ThumbnailRenderer>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ThumbnailRenderer))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    void ThumbnailRenderer::init(ResourceContext& context, uint32_t width, uint32_t height) {
        this->resourceContext = &context;

        camera = ghnew Camera();
        camera->initParameters(context.ParameterManager);
        camera->setScreenSize(width, height);

        /*step = ghnew RenderStep();
        step->initParameters(context.ParameterManager);
        step->Camera = camera;*/

        renderer = ghnew Renderer();
        XMFLOAT4 color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1);
        renderer->ClearColor = &color;

        renderTarget = ghnew RenderTarget();
        renderTarget->init(context.Graphics, width, height, DXGI_FORMAT_R8G8B8A8_UNORM);
        depthBuffer = ghnew DepthBuffer();
        depthBuffer->init(context.Graphics, width, height);

        frame = ghnew Frame();
        D3D12_VIEWPORT viewport = D3D12_VIEWPORT{0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height),0,1};
        D3D12_RECT scissorRect = D3D12_RECT{0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
        frame->init(context.Graphics, viewport, scissorRect, renderTarget, depthBuffer);

        renderer->init(context);
    }

    Status ThumbnailRenderer::render(DrawableComponent& entity, Image*& image) {
        CameraUtils::lookAtEntity(*camera, entity);

		CommandList& commandList = renderer->startFrame(*frame);
		//renderer->draw(entity, commandList);
		renderer->finishFrame(*frame);
        frame->CommandList.wait();

        return renderTarget->capture(*resourceContext, image);
    }

    Status ThumbnailRenderer::render(Mesh& mesh, Image*& image) {
        /*Model* model = ghnew Model();
        model->Mesh = &mesh;
        model->Material = Materials::makeChecker(*resourceContext);
        model->Valid = true;

        Status result = render(*model, image);

        model->release();
		*/
		return Status::OK;// result;
    }

    Status ThumbnailRenderer::render(Material& material, Image*& image) {
        /*Model* model = Models::makeSphere(*resourceContext, material);

        BoundingOrientedBox boundingBox;
        XMFLOAT4X4 localTransformation = model->getTransformation();
        BoundingOrientedBox::CreateFromBoundingBox(boundingBox, *model->BoundingBox);
        boundingBox.Transform(boundingBox, XMLoadFloat4x4(&localTransformation));

        Status result = render(*model, image);

        model->release();
		*/
		return Status::OK;// result;
    }
}