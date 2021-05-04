#include "ghpch.h"
#include "Graphics2D.h"

#include "graphics/Graphics.h"
#include "graphics/buffer/RenderTarget.h"

namespace Ghurund {
    Status Graphics2D::init(Graphics& graphics) {
        UINT d3d11DeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        D2D1_FACTORY_OPTIONS d2dFactoryOptions = {};

#if defined(_DEBUG)
        // Enable the D2D debug layer.
        d2dFactoryOptions.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

        // Enable the D3D11 debug layer.
        d3d11DeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

        ComPtr<ID3D12InfoQueue> d3dInfoQueue;
        HRESULT hr = graphics.Device->QueryInterface(__uuidof(ID3D12InfoQueue), &d3dInfoQueue);
        if (SUCCEEDED(hr)) {
            D3D12_MESSAGE_ID hide[] = {
                D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,
            };
            D3D12_INFO_QUEUE_FILTER filter;
            memset(&filter, 0, sizeof(filter));
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            hr = d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
#endif

        // Create an 11 device wrapped around the 12 device and share
        // 12's command queue.
        ComPtr<ID3D11Device> d3d11Device;
        ID3D12CommandQueue* ppCommandQueues[] = { graphics.DirectQueue };
        if (FAILED(D3D11On12CreateDevice(
            graphics.Device,
            d3d11DeviceFlags,
            nullptr,
            0,
            reinterpret_cast<IUnknown**>(ppCommandQueues),
            _countof(ppCommandQueues),
            0,
            &d3d11Device,
            &m_d3d11DeviceContext,
            nullptr
        )))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "D3D11On12CreateDevice failed\n");

        // Query the 11On12 device from the 11 device.
        if (FAILED(d3d11Device.As(&m_d3d11On12Device)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "cast to 11On12 device failed\n");

#if defined(_DEBUG)
        // Filter a debug error coming from the 11on12 layer.
        ComPtr<ID3D12InfoQueue> infoQueue;
        if (SUCCEEDED(graphics.Device->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
            // Suppress messages based on their severity level.
            D3D12_MESSAGE_SEVERITY severities[] = {
                D3D12_MESSAGE_SEVERITY_INFO,
            };

            // Suppress individual messages by their ID.
            D3D12_MESSAGE_ID denyIds[] = {
                // This occurs when there are uninitialized descriptors in a descriptor table, even when a
                // shader does not access the missing descriptors.
                D3D12_MESSAGE_ID_INVALID_DESCRIPTOR_HANDLE,
            };

            D3D12_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumSeverities = _countof(severities);
            filter.DenyList.pSeverityList = severities;
            filter.DenyList.NumIDs = _countof(denyIds);
            filter.DenyList.pIDList = denyIds;

            if (FAILED(infoQueue->PushStorageFilter(&filter)))
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "PushStorageFilter failed\n");
        }
#endif

        ComPtr<IDXGIDevice> dxgiDevice;
        if (FAILED(m_d3d11On12Device.As(&dxgiDevice)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "m_d3d11On12Device.As(&dxgiDevice) failed\n");

        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory6), &d2dFactoryOptions, &m_d2dFactory)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "D2D1CreateFactory failed\n");
        if (FAILED(m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateDevice failed\n");

        if (FAILED(m_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &deviceContext)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateDeviceContext failed\n");

        if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory5), &m_dwriteFactory)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "DWriteCreateFactory failed\n");

        return Status::OK;
    }

    void Graphics2D::uninit() {
        deviceContext.Reset();
        m_d3d11DeviceContext.Reset();
        m_d3d11On12Device.Reset();
        m_dwriteFactory.Reset();
        m_d2dFactory.Reset();
        m_d2dDevice.Reset();
        currentTarget = nullptr;
    }

    Status Graphics2D::beginPaint(RenderTarget& target) {
#ifdef _DEBUG
        if (state != UIState::IDLE)
            Logger::log(LogType::WARNING, Status::INV_STATE, "UI is not in IDLE state\n");
#endif
        currentTarget = &target;
        deviceContext->SetTarget(currentTarget->Target2D);

        auto wrappedTarget = currentTarget->WrappedTarget;
        m_d3d11On12Device->AcquireWrappedResources(&wrappedTarget, 1);
        deviceContext->BeginDraw();
        deviceContext->Clear();

        state = UIState::RECORDING;
        return Status::OK;
    }

    Status Graphics2D::endPaint() {
#ifdef _DEBUG
        if (state != UIState::RECORDING)
            Logger::log(LogType::WARNING, Status::INV_STATE, "UI is not in RECORDING state\n");
#endif

        HRESULT endDrawResult = deviceContext->EndDraw();
        if (FAILED(endDrawResult))
            return Logger::log(LogType::WARNING, Status::CALL_FAIL, "ID2D1DeviceContext2::EndDraw() failed with code {}\n", endDrawResult);

        auto wrappedTarget = currentTarget->WrappedTarget;
        m_d3d11On12Device->ReleaseWrappedResources(&wrappedTarget, 1);

        m_d3d11DeviceContext->Flush();

        state = UIState::IDLE;
        return Status::OK;
    }
}
