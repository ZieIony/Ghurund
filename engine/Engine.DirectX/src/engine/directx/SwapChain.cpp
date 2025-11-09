#include "ghedxpch.h"
#include "SwapChain.h"

#include "DxGraphics.h"
#include "core/window/SystemWindow.h"
#include "core/logging/Logger.h"
#include "core/logging/Formatter.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& SwapChain::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<SwapChain>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void SwapChain::init(DxGraphics& graphics, HWND handle, IntSize size, uint32_t frameCount) {
        this->graphics = &graphics;
        this->frameCount = frameCount;
        this->format = DXGI_FORMAT_R8G8B8A8_UNORM;
        this->size = size;

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.BufferCount = frameCount;
        swapChainDesc.Width = size.Width;
        swapChainDesc.Height = size.Height;
        swapChainDesc.Format = format;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.SampleDesc.Count = 1;

        ComPtr<IDXGISwapChain1> swapChain1;
        if (FAILED(graphics.Factory->CreateSwapChainForHwnd(graphics.DirectQueue, handle, &swapChainDesc, nullptr, nullptr, &swapChain1))) {
            Logger::log(LogType::ERR0R, _T("factory->CreateSwapChainForHwnd() failed\n"));
            throw CallFailedException("factory->CreateSwapChainForHwnd() failed");
        }

        if (FAILED(swapChain1.As(&swapChain))) {
            Logger::log(LogType::ERR0R, _T("swapChain1.As() failed\n"));
            throw CallFailedException("factory->CreateSwapChainForHwnd() failed");
        }
    }

    void SwapChain::initBuffers() {
        if (frames || size.Width == 0 || size.Height == 0)
            throw InvalidStateException();

        D3D12_VIEWPORT viewport = D3D12_VIEWPORT{ 0.0f, 0.0f, (float)size.Width, (float)size.Height,0,1 };
        D3D12_RECT scissorRect = D3D12_RECT{ 0, 0, (LONG)size.Width, (LONG)size.Height };

        frames = ghnew Array<Frame>(frameCount);
        for (unsigned int i = 0; i < frameCount; i++) {
            ID3D12Resource* renderTargetBuffer;
            swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargetBuffer));
            RenderTarget* renderTarget = ghnew RenderTarget();
            renderTarget->init(*graphics, renderTargetBuffer);

            DepthBuffer* depthBuffer = ghnew DepthBuffer();
            depthBuffer->init(*graphics, size);

            frames->get(i).init(*graphics, viewport, scissorRect, renderTarget, depthBuffer);
            renderTargetBuffer->Release();
        }
    }

    void SwapChain::uninitBuffers() {
        if (frames == nullptr)
            return;

        delete frames;
        frames = nullptr;
        currentFrame = 0;
    }

    void SwapChain::present() {
        currentFrame++;
        currentFrame %= frameCount;

        HRESULT hr = swapChain->Present(1, 0);
        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
            Logger::log(LogType::ERR0R, _T("swapChain->Present() failed - device lost\n"));
            throw InvalidStateException();
        } else if (FAILED(hr)) {
            Logger::log(LogType::ERR0R, _T("swapChain->Present() failed\n"));
            throw CallFailedException();
        }
    }

    void SwapChain::setSize(const IntSize& size) {
        this->size = size;
        if (size.Width > 0 && size.Height > 0) {
            HRESULT hr = swapChain->ResizeBuffers(frameCount, size.Width, size.Height, format, 0);
            if (FAILED(hr)) {
                Logger::log(LogType::ERR0R, _T("swapChain->ResizeBuffers() failed\n"));
                throw CallFailedException();
            }
        }
    }

}