#include "ghcdxpch.h"
#include "Frame.h"

#include "Graphics.h"

namespace Ghurund::Core::DirectX {
    Status Frame::init(Graphics& graphics, D3D12_VIEWPORT& viewport, D3D12_RECT& scissorRect, Ghurund::Core::DirectX::RenderTarget* renderTarget, DepthBuffer* depthBuffer) {
        this->renderTarget = renderTarget;
        this->depthBuffer = depthBuffer;
        this->viewport = viewport;
        this->scissorRect = scissorRect;

        commandList->init(graphics, graphics.DirectQueue);
        commandList->Name = L"frame command list";

        return Status::OK;
    }

    Status Frame::start(::DirectX::XMFLOAT4* color) {
        commandList->wait();
        commandList->reset();

        commandList->get()->OMSetRenderTargets(1, &renderTarget->Handle, FALSE, &depthBuffer->Handle);
        renderTarget->start(*commandList);

        commandList->get()->RSSetViewports(1, &viewport);
        commandList->get()->RSSetScissorRects(1, &scissorRect);

        if (color != nullptr)
            renderTarget->clear(*commandList, *color);
        depthBuffer->clear(*commandList);

        return Status::OK;
    }

    Status Frame::finish() {
        renderTarget->finish(*commandList);
        return commandList->finish();
    }

    void Frame::flush() {
        commandList->finish();
        commandList->wait();
        commandList->reset();
    }
}