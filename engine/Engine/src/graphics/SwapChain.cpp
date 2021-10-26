#include "ghpch.h"
#include "SwapChain.h"

#include "Graphics.h"
#include "core/window/SystemWindow.h"
#include "core/logging/Logger.h"
#include "core/logging/Formatter.h"

namespace Ghurund {
    const Ghurund::Core::Type& SwapChain::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<SwapChain>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<SwapChain>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(SwapChain))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(Object::TYPE);

        return TYPE;
    }

    Status SwapChain::init(Graphics& graphics, SystemWindow& window, uint32_t frameCount) {
        this->graphics = &graphics;
        this->window = &window;
        this->frameCount = frameCount;
        this->format = DXGI_FORMAT_R8G8B8A8_UNORM;

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.BufferCount = frameCount;
        swapChainDesc.Width = window.Size.width;
        swapChainDesc.Height = window.Size.height;
        swapChainDesc.Format = format;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.SampleDesc.Count = 1;

        ComPtr<IDXGISwapChain1> swapChain1;
        if (FAILED(graphics.Factory->CreateSwapChainForHwnd(graphics.DirectQueue, window.Handle, &swapChainDesc, nullptr, nullptr, &swapChain1)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("factory->CreateSwapChainForHwnd() failed\n"));

        if (FAILED(swapChain1.As(&swapChain)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("swapChain1.As() failed\n"));

        return Status::OK;
    }

    Status SwapChain::initBuffers() {
        if (frames || window->Size.width == 0 || window->Size.height == 0)
            return Status::INV_STATE;

        D3D12_VIEWPORT viewport = D3D12_VIEWPORT{ 0.0f, 0.0f, (float)window->Size.width, (float)window->Size.height,0,1 };
        D3D12_RECT scissorRect = D3D12_RECT{ 0, 0, (LONG)window->Size.width, (LONG)window->Size.height };

        frames = ghnew Array<Frame>(frameCount);
        for (unsigned int i = 0; i < frameCount; i++) {
            ID3D12Resource* renderTargetBuffer;
            swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargetBuffer));
            RenderTarget* renderTarget = ghnew RenderTarget();
            renderTarget->init(*graphics, renderTargetBuffer);

            DepthBuffer* depthBuffer = ghnew DepthBuffer();
            depthBuffer->init(*graphics, window->Size.width, window->Size.height);

            frames->get(i).init(*graphics, viewport, scissorRect, renderTarget, depthBuffer);
            renderTargetBuffer->Release();
        }

        return Status::OK;
    }

    void SwapChain::uninitBuffers() {
        if (frames == nullptr)
            return;

        delete frames;
        frames = nullptr;
        currentFrame = 0;
    }

    Status SwapChain::present() {
        currentFrame++;
        currentFrame %= frameCount;

        HRESULT hr = swapChain->Present(1, 0);
        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
            return Logger::log(LogType::ERR0R, Status::DEVICE_LOST, _T("swapChain->Present() failed\n"));
        } else if (FAILED(hr)) {
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("swapChain->Present() failed\n"));
        }

        return Status::OK;
    }

    Status SwapChain::resize(unsigned int width, unsigned int height) {
        if (width > 0 && height > 0) {
            HRESULT hr = swapChain->ResizeBuffers(frameCount, width, height, format, 0);
            if (FAILED(hr))
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("swapChain->ResizeBuffers() failed\n"));
        }

        return Status::OK;
    }

}