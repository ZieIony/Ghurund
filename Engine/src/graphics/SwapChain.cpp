#include "SwapChain.h"
#include "Graphics.h"

namespace Ghurund {
    Status SwapChain::init(Graphics &graphics, Window &window, unsigned int frameCount) {
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.BufferCount = frameCount;
        swapChainDesc.Width = window.Width;
        swapChainDesc.Height = window.Height;
        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.SampleDesc.Count = 1;

        ComPtr<IDXGISwapChain1> swapChain1;
        if(FAILED(graphics.getFactory()->CreateSwapChainForHwnd(graphics.getCommandQueue().Get(), window.Handle, &swapChainDesc, nullptr, nullptr, &swapChain1))) {
            Logger::log(_T("factory->CreateSwapChainForHwnd() failed\n"));
            return Status::CALL_FAIL;
        }

        if(FAILED(swapChain1.As(&swapChain))) {
            Logger::log(_T("swapChain1.As() failed\n"));
            return Status::CALL_FAIL;
        }

        frames = ghnew Frame[frameCount];
        for(unsigned int i = 0; i < frameCount; i++) {
            ComPtr<ID3D12Resource> renderTargetBuffer;
            swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargetBuffer));

            shared_ptr<RenderTarget> renderTarget(ghnew RenderTarget());
            renderTarget->init(graphics, renderTargetBuffer);

            shared_ptr<DepthBuffer> depthBuffer(ghnew DepthBuffer());
            depthBuffer->init(graphics, window);

            frames[i].init(graphics, window, renderTarget, depthBuffer);
        }

        frameBuffer.init(frames, frameCount);

        return Status::OK;
    }
}