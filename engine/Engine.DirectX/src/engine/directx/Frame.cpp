#include "ghedxpch.h"
#include "Frame.h"

#include "DxGraphics.h"

namespace Ghurund::Engine::DirectX {
    void Frame::init(DxGraphics& graphics, D3D12_VIEWPORT& viewport, D3D12_RECT& scissorRect, Ghurund::Engine::DirectX::RenderTarget* renderTarget, DepthBuffer* depthBuffer) {
        this->renderTarget = renderTarget;
        this->depthBuffer = depthBuffer;
        this->viewport = viewport;
        this->scissorRect = scissorRect;

        startCommandList->init(graphics, graphics.DirectQueue);
        startCommandList->Name = L"start command list";
        renderCommandList->init(graphics, graphics.DirectQueue);
        renderCommandList->Name = L"render command list";
    }

    void Frame::start() {
		if (startCommandList->State == CommandListState::CLOSED)
            startCommandList->wait();
        startCommandList->reset();

        startCommandList->get()->OMSetRenderTargets(1, &renderTarget->Handle, FALSE, &depthBuffer->Handle);
        renderTarget->start(*startCommandList);

        startCommandList->get()->RSSetViewports(1, &viewport);
        startCommandList->get()->RSSetScissorRects(1, &scissorRect);
    }

    void Frame::startFrame(CommandList& commandList) {
        if (commandList.State == CommandListState::CLOSED)
            commandList.wait();
        commandList.reset();
        commandList.get()->OMSetRenderTargets(1, &renderTarget->Handle, FALSE, &depthBuffer->Handle);
        commandList.get()->RSSetViewports(1, &viewport);
        commandList.get()->RSSetScissorRects(1, &scissorRect);
    }

    void Frame::clear(const Color* color) {
        if (color != nullptr)
            renderTarget->clear(*startCommandList, { color->R, color->G, color->B, color->A });
        depthBuffer->clear(*startCommandList);
        startCommandList->finish();

        if (renderCommandList->State == CommandListState::CLOSED)
            renderCommandList->wait();
        renderCommandList->reset();
        renderCommandList->get()->OMSetRenderTargets(1, &renderTarget->Handle, FALSE, &depthBuffer->Handle);
        renderCommandList->get()->RSSetViewports(1, &viewport);
        renderCommandList->get()->RSSetScissorRects(1, &scissorRect);
    }

    void Frame::finish() {
        renderTarget->finish(*renderCommandList);
        renderCommandList->finish();
    }

    void Frame::flush() {
        renderCommandList->finish();
        renderCommandList->wait();
        renderCommandList->reset();
    }
}
