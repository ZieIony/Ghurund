#include "ghuidxpch.h"
#include "Graphics2D.h"

#include "core/Exceptions.h"


namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Direct2D::Graphics2D>() {
        static Type TYPE = Type(Ghurund::UI::Direct2D::NAMESPACE_NAME, "Graphics2D", sizeof(Ghurund::UI::Direct2D::Graphics2D));
        return TYPE;
    }
}

namespace Ghurund::UI::Direct2D {
    void Graphics2D::init(ID3D12Device& device, ID3D12CommandQueue& commandQueue) {
        UINT d3d11DeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        D2D1_FACTORY_OPTIONS d2dFactoryOptions = {};

#if defined(_DEBUG)
        // Enable the D2D debug layer.
        d2dFactoryOptions.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

        // Enable the D3D11 debug layer.
        d3d11DeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

        ComPtr<ID3D12InfoQueue> infoQueue;
        HRESULT hr = device.QueryInterface(__uuidof(ID3D12InfoQueue), &infoQueue);
        if (SUCCEEDED(hr)) {
            // Suppress messages based on their severity level.
            D3D12_MESSAGE_SEVERITY severities[] = {
                D3D12_MESSAGE_SEVERITY_INFO,
            };

            // Suppress individual messages by their ID.
            D3D12_MESSAGE_ID denyIds[] = {
                // This occurs when there are uninitialized descriptors in a descriptor table, even when a
                // shader does not access the missing descriptors.
                D3D12_MESSAGE_ID_INVALID_DESCRIPTOR_HANDLE,
                D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE
            };

            D3D12_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumSeverities = _countof(severities);
            filter.DenyList.pSeverityList = severities;
            filter.DenyList.NumIDs = _countof(denyIds);
            filter.DenyList.pIDList = denyIds;

            if (FAILED(infoQueue->PushStorageFilter(&filter))) {
                Logger::log(LogType::ERR0R, _T("PushStorageFilter failed\n"));
                throw CallFailedException();
            }
        }
#endif

        // Create an 11 device wrapped around the 12 device and share
        // 12's command queue.
        ComPtr<ID3D11Device> d3d11Device;
        ID3D12CommandQueue* ppCommandQueues[] = { &commandQueue };
        if (FAILED(D3D11On12CreateDevice(
            &device,
            d3d11DeviceFlags,
            nullptr,
            0,
            reinterpret_cast<IUnknown**>(ppCommandQueues),
            _countof(ppCommandQueues),
            0,
            &d3d11Device,
            &d3d11DeviceContext,
            nullptr
        ))) {
            return Logger::log(LogType::ERR0R, _T("D3D11On12CreateDevice failed\n"));
            throw CallFailedException();
        }

        // Query the 11On12 device from the 11 device.
        if (FAILED(d3d11Device.As(&d3d11On12Device))) {
            Logger::log(LogType::ERR0R, _T("cast to 11On12 device failed\n"));
            throw CallFailedException();
        }

        ComPtr<IDXGIDevice> dxgiDevice;
        if (FAILED(d3d11On12Device.As(&dxgiDevice))) {
            Logger::log(LogType::ERR0R, _T("d3d11On12Device.As(&dxgiDevice) failed\n"));
            throw CallFailedException();
        }

        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory6), &d2dFactoryOptions, &d2dFactory))) {
            Logger::log(LogType::ERR0R, _T("D2D1CreateFactory failed\n"));
            throw CallFailedException();
        }
        if (FAILED(d2dFactory->CreateDevice(dxgiDevice.Get(), &d2dDevice))) {
            Logger::log(LogType::ERR0R, _T("CreateDevice failed\n"));
            throw CallFailedException();
        }

        if (FAILED(d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &deviceContext))) {
            Logger::log(LogType::ERR0R, _T("CreateDeviceContext failed\n"));
            throw CallFailedException();
        }

        if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory5), &dwriteFactory))) {
            Logger::log(LogType::ERR0R, _T("DWriteCreateFactory failed\n"));
            throw CallFailedException();
        }
    }

    void Graphics2D::uninit() {
        dwriteFactory.Reset();
        deviceContext.Reset();
        d2dDevice.Reset();
        d2dFactory.Reset();
        d3d11On12Device.Reset();
        d3d11DeviceContext.Reset();
    }

    Status Graphics2D::beginPaint(RenderTarget2D& target) {
#ifdef _DEBUG
        if (state != UIState::IDLE)
            Logger::log(LogType::WARNING, Status::INV_STATE, _T("UI is not in IDLE state\n"));
#endif
        deviceContext->SetTarget(target.Target2D);

        auto wrappedTarget = target.WrappedTarget;
        d3d11On12Device->AcquireWrappedResources(&wrappedTarget, 1);
        deviceContext->BeginDraw();
        deviceContext->Clear();

        state = UIState::RECORDING;
        return Status::OK;
    }

    Status Graphics2D::endPaint(RenderTarget2D& target) {
#ifdef _DEBUG
        if (state != UIState::RECORDING)
            Logger::log(LogType::WARNING, Status::INV_STATE, _T("UI is not in RECORDING state\n"));
#endif

        HRESULT endDrawResult = deviceContext->EndDraw();

        auto wrappedTarget = target.WrappedTarget;
        d3d11On12Device->ReleaseWrappedResources(&wrappedTarget, 1);

        d3d11DeviceContext->Flush();
        deviceContext->SetTarget(nullptr);

        state = UIState::IDLE;

        if (FAILED(endDrawResult)) {
            auto text = std::format(_T("ID2D1DeviceContext2::EndDraw() failed with code {}\n"), endDrawResult);
            return Logger::log(LogType::WARNING, Status::CALL_FAIL, text.c_str());
        }
        return Status::OK;
    }
}
