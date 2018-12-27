#include "Frame.h"
#include "Graphics.h"

namespace Ghurund {
    Status Frame::init(Graphics &graphics, Window &window, RenderTarget *renderTarget, DepthBuffer *depthBuffer) {
        this->renderTarget = renderTarget;
        this->depthBuffer = depthBuffer;
        viewport = window.getViewport();
        scissorRect = window.getScissorRect();

        commandList->init(graphics, graphics.DirectQueue);
        commandList->Name = _T("frame command list");

        return Status::OK;
    }

    Status Frame::start(XMFLOAT4 *color) {
        commandList->wait();
        commandList->reset();

        commandList->get()->OMSetRenderTargets(1, &renderTarget->getHandle(), FALSE, &depthBuffer->getHandle());
        renderTarget->start(*commandList);

        commandList->get()->RSSetViewports(1, &viewport);
        commandList->get()->RSSetScissorRects(1, &scissorRect);

        if(color!=nullptr)
            renderTarget->clear(*commandList, *color);
        depthBuffer->clear(*commandList);

        return Status::OK;
    }

    Status Frame::finish() {
        renderTarget->finish(*commandList);
        commandList->finish();

        return Status::OK;
    }
}