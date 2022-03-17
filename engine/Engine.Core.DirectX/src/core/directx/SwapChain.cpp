#include "ghcdxpch.h"
#include "SwapChain.h"

#include "Graphics.h"
#include "core/window/SystemWindow.h"
#include "core/logging/Logger.h"
#include "core/logging/Formatter.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core::DirectX {
    const Ghurund::Core::Type& SwapChain::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<SwapChain>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<SwapChain>(Ghurund::Core::DirectX::NAMESPACE_NAME, GH_STRINGIFY(SwapChain))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void SwapChain::init(Graphics& graphics, SystemWindow& window, uint32_t frameCount) {
        this->graphics = &graphics;
        this->window = &window;
        this->frameCount = frameCount;
        this->format = DXGI_FORMAT_R8G8B8A8_UNORM;

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.BufferCount = frameCount;
        swapChainDesc.Width = window.Size.Width;
        swapChainDesc.Height = window.Size.Height;
        swapChainDesc.Format = format;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.SampleDesc.Count = 1;

        ComPtr<IDXGISwapChain1> swapChain1;
        if (FAILED(graphics.Factory->CreateSwapChainForHwnd(graphics.DirectQueue, window.Handle, &swapChainDesc, nullptr, nullptr, &swapChain1))) {
            Logger::log(LogType::ERR0R, _T("factory->CreateSwapChainForHwnd() failed\n"));
            throw CallFailedException("factory->CreateSwapChainForHwnd() failed");
        }

        if (FAILED(swapChain1.As(&swapChain))) {
            Logger::log(LogType::ERR0R, _T("swapChain1.As() failed\n"));
            throw CallFailedException("factory->CreateSwapChainForHwnd() failed");
        }
    }

    Status SwapChain::initBuffers() {
        if (frames || window->Size.Width == 0 || window->Size.Height == 0)
            return Status::INV_STATE;

        D3D12_VIEWPORT viewport = D3D12_VIEWPORT{ 0.0f, 0.0f, (float)window->Size.Width, (float)window->Size.Height,0,1 };
        D3D12_RECT scissorRect = D3D12_RECT{ 0, 0, (LONG)window->Size.Width, (LONG)window->Size.Height };

        frames = ghnew Array<Frame>(frameCount);
        for (unsigned int i = 0; i < frameCount; i++) {
            ID3D12Resource* renderTargetBuffer;
            swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargetBuffer));
            RenderTarget* renderTarget = ghnew RenderTarget();
            renderTarget->init(*graphics, renderTargetBuffer);

            DepthBuffer* depthBuffer = ghnew DepthBuffer();
            depthBuffer->init(*graphics, window->Size.Width, window->Size.Height);

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

    Status SwapChain::resize(const IntSize& size) {
        if (size.Width > 0 && size.Height > 0) {
            HRESULT hr = swapChain->ResizeBuffers(frameCount, size.Width, size.Height, format, 0);
            if (FAILED(hr))
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("swapChain->ResizeBuffers() failed\n"));
        }

        return Status::OK;
    }

}