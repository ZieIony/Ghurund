#include "ghedxpch.h"
#include "Frame.h"

#include "Graphics.h"

namespace Ghurund::Engine::DirectX {
    void Frame::init(Graphics& graphics, D3D12_VIEWPORT& viewport, D3D12_RECT& scissorRect, Ghurund::Engine::DirectX::RenderTarget* renderTarget, DepthBuffer* depthBuffer) {
        this->renderTarget = renderTarget;
        this->depthBuffer = depthBuffer;
        this->viewport = viewport;
        this->scissorRect = scissorRect;

        commandList->init(graphics, graphics.DirectQueue);
        commandList->Name = L"frame command list";
    }

    void Frame::start(::DirectX::XMFLOAT4* color) {
		if (commandList->State == CommandListState::CLOSED)
			commandList->wait();
        commandList->reset();

        commandList->get()->OMSetRenderTargets(1, &renderTarget->Handle, FALSE, &depthBuffer->Handle);
        renderTarget->start(*commandList);

        commandList->get()->RSSetViewports(1, &viewport);
        commandList->get()->RSSetScissorRects(1, &scissorRect);

        if (color != nullptr)
            renderTarget->clear(*commandList, *color);
        depthBuffer->clear(*commandList);
    }

    void Frame::finish() {
        renderTarget->finish(*commandList);
        commandList->finish();
    }

    void Frame::flush() {
        commandList->finish();
        commandList->wait();
        commandList->reset();
    }
}