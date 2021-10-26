#pragma once

#include "core/Pointer.h"
#include "ui/direct2d/font/FontCollectionLoader.h"
#include "RenderTarget2D.h"

#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <dwrite_3.h>
#include <d3d11on12.h>
#include <wrl.h>

namespace Ghurund::UI::Direct2D {
    using Microsoft::WRL::ComPtr;
    using namespace Ghurund::UI;

    enum class UIState {
        RECORDING, IDLE
    };

    class Graphics2D {
    private:
        ComPtr<ID2D1DeviceContext5> deviceContext;
        ComPtr<ID3D11DeviceContext> d3d11DeviceContext;
        ComPtr<ID3D11On12Device> d3d11On12Device;
        ComPtr<IDWriteFactory5> dwriteFactory;
        ComPtr<ID2D1Factory6> d2dFactory;
        ComPtr<ID2D1Device5> d2dDevice;
        UIState state = UIState::IDLE;

    public:
        ~Graphics2D() {
            uninit();
        }

        inline ID2D1Device5* getDevice() {
            return d2dDevice.Get();
        };

        __declspec(property(get = getDevice)) ID2D1Device5* Device;

        inline ID2D1DeviceContext5& getDeviceContext() {
            return *deviceContext.Get();
        };

        __declspec(property(get = getDeviceContext)) ID2D1DeviceContext5& DeviceContext;

        inline ID3D11On12Device* getDevice11() {
            return d3d11On12Device.Get();
        };

        __declspec(property(get = getDevice11)) ID3D11On12Device* Device11;

        inline ID2D1Factory6* getD2dFactory() {
            return d2dFactory.Get();
        };

        __declspec(property(get = getD2dFactory)) ID2D1Factory6* D2DFactory;

        inline IDWriteFactory5* getDWriteFactory() {
            return dwriteFactory.Get();
        };

        __declspec(property(get = getDWriteFactory)) IDWriteFactory5* DWriteFactory;

        inline UIState getState() const {
            return state;
        }

        __declspec(property(get = getState)) UIState State;

        void init(ID3D12Device& device, ID3D12CommandQueue& commandQueue);

        void uninit();

        Status beginPaint(RenderTarget2D& target);

        Status endPaint(RenderTarget2D& target);

        void flush() {
            d3d11DeviceContext->Flush();
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Direct2D::Graphics2D>();
}