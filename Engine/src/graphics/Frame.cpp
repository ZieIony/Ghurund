#include "Frame.h"
#include "Graphics.h"

namespace Ghurund {
    Status Frame::init(Graphics &graphics, Window &window, shared_ptr<RenderTarget> renderTarget, shared_ptr<DepthBuffer> depthBuffer) {
        this->renderTarget = renderTarget;
        this->depthBuffer = depthBuffer;
        viewport = window.getViewport();
        scissorRect = window.getScissorRect();

        commandList.reset(ghnew CommandList());
        commandList->init(graphics);

        return Status::OK;
    }

    Status Frame::start() {
        commandList->wait();
        commandList->reset();

        commandList->get()->OMSetRenderTargets(1, &renderTarget->getHandle(), FALSE, &depthBuffer->getHandle());
        renderTarget->start(commandList);

        commandList->get()->RSSetViewports(1, &viewport);
        commandList->get()->RSSetScissorRects(1, &scissorRect);
        
        renderTarget->clear(commandList);
        depthBuffer->clear(commandList);

        return Status::OK;
    }

    Status Frame::finish() {
        renderTarget->finish(commandList);
        commandList->finish();

        return Status::OK;
    }
}