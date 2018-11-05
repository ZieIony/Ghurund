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

        initAdapters();
        ComPtr<IDXGIAdapter1> adapter = adapters[0]->get();
        if(FAILED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)))) {
            Logger::log(_T("D3D12CreateDevice failed\n"));
            return Status::CALL_FAIL;
        }

        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

        if(FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&directQueue)))) {
            Logger::log(_T("create direct queue failed\n"));
            return Status::CALL_FAIL;
        }

        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;

        if(FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&computeQueue)))) {
            Logger::log(_T("create compute queue failed\n"));
            return Status::CALL_FAIL;
        }

        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;

        if(FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&copyQueue)))) {
            Logger::log(_T("create copy queue failed\n"));
            return Status::CALL_FAIL;
        }

        /*if(FAILED(factory->MakeWindowAssociation(window.Handle, DXGI_MWA_NO_ALT_ENTER))) {
            Logger::log(_T("factory->MakeWindowAssociation() failed\n"));
            return Status::CALL_FAIL;
        }*/

        // TODO: do it properly
        allocator.allocate(*this, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        allocator.allocate(*this, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

        return Status::OK;
    }

}