#include "Graphics.h"
#include "core/Logger.h"

#include <D3Dcompiler.h>

namespace Ghurund {

    Status Graphics::init() {
        UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)
        ComPtr<ID3D12Debug> debugController;
        if(SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
            debugController->EnableDebugLayer();

            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
#endif

        if(FAILED(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)))) {
            Logger::log(_T("failed to create DXGIFactory2"));
            return Status::CALL_FAIL;
        }

        if(software) {
            ComPtr<IDXGIAdapter> warpAdapter;
            if(FAILED(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)))) {
                Logger::log(_T("factory->EnumWarpAdapter() failed\n"));
                return Status::CALL_FAIL;
            }

            if(FAILED(D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)))) {
                Logger::log(_T("D3D12CreateDevice failed\n"));
                return Status::CALL_FAIL;
            }
        } else {
            ComPtr<IDXGIAdapter1> adapter;
            bool done = false;
            DXGI_ADAPTER_DESC1 desc;

            for(unsigned int adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex) {
                adapter->GetDesc1(&desc);

                if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                    continue;

                if(SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)))) {
                    done = true;
                    break;
                }
            }

            if(!done)
                return Status::DIRECTX12_NOT_SUPPORTED;
        }

        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

        if(FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)))) {
            Logger::log(_T("device->CreateCommandQueue() failed\n"));
            return Status::CALL_FAIL;
        }

        /*if(FAILED(factory->MakeWindowAssociation(window.Handle, DXGI_MWA_NO_ALT_ENTER))) {
            Logger::log(_T("factory->MakeWindowAssociation() failed\n"));
            return Status::CALL_FAIL;
        }*/

        return Status::OK;
    }

}