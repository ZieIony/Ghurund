#include "SwapChain.h"
#include "Graphics.h"

namespace Ghurund {
    const Ghurund::Type& SwapChain::TYPE = Ghurund::Type([]() {return ghnew SwapChain(); }, "SwapChain");
  
    Status SwapChain::init(Graphics &graphics, Window &window, unsigned int frameCount) {
        this->graphics = &graphics;
        this->window = &window;
        this->frameCount = frameCount;
        this->format = DXGI_FORMAT_R8G8B8A8_UNORM;

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.BufferCount = frameCount;
        swapChainDesc.Width = window.Width;
        swapChainDesc.Height = window.Height;
        swapChainDesc.Format = format;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.SampleDesc.Count = 1;

        ComPtr<IDXGISwapChain1> swapChain1;
        if(FAILED(graphics.Factory->CreateSwapChainForHwnd(graphics.DirectQueue, window.Handle, &swapChainDesc, nullptr, nullptr, &swapChain1)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("factory->CreateSwapChainForHwnd() failed\n"));

        if(FAILED(swapChain1.As(&swapChain)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("swapChain1.As() failed\n"));

        return initBuffers();
    }

    Status SwapChain::initBuffers() {
        if(window->Width==0||window->Height==0)
            return Status::INV_STATE;

        frames = ghnew Frame[frameCount];
        for(unsigned int i = 0; i < frameCount; i++) {
            ID3D12Resource *renderTargetBuffer;
            swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargetBuffer));

            RenderTarget *renderTarget = ghnew RenderTarget();
            renderTarget->init(*graphics, renderTargetBuffer);

            DepthBuffer *depthBuffer = ghnew DepthBuffer();
            depthBuffer->init(*graphics, window->Width, window->Height);

            frames[i].init(*graphics, window->getViewport(), window->getScissorRect(), renderTarget, depthBuffer);
        }

        frameBuffer.init(frames, frameCount);

        return Status::OK;
    }

    void SwapChain::uninitBuffers() {
        if(frames==nullptr)
            return;

        Ghurund::CommandList &commandList = frameBuffer->CommandList;
        if(commandList.State==CommandListState::RECORDING) {
            commandList.get()->OMSetRenderTargets(0, 0, true, 0);
            commandList.finish();
        }
        if(commandList.State==CommandListState::CLOSED)
            commandList.wait();
        delete[] frames;
        frames = nullptr;
    }

    void SwapChain::resize(unsigned int width, unsigned int height) {
        uninitBuffers();
        if(width>0&&height>0)
            swapChain->ResizeBuffers(frameCount, width, height, format, 0);
        initBuffers();
    }

}