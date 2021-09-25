#include "ghpch.h"
#include "Graphics.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "DirectXTypes.h"

#include <D3Dcompiler.h>

namespace Ghurund {
    const Ghurund::Core::Type& Graphics::GET_TYPE() {
        static auto PROPERTY_DEVICE = Ghurund::ReadOnlyProperty<Graphics, ID3D12Device*>("Device", (ID3D12Device * (Graphics::*)()) & getDevice);
        static auto PROPERTY_DIRECTQUEUE = Ghurund::ReadOnlyProperty<Graphics, ID3D12CommandQueue*>("DirectQueue", (ID3D12CommandQueue * (Graphics::*)()) & getDirectQueue);
        static auto PROPERTY_COMPUTEQUEUE = Ghurund::ReadOnlyProperty<Graphics, ID3D12CommandQueue*>("ComputeQueue", (ID3D12CommandQueue * (Graphics::*)()) & getComputeQueue);
        static auto PROPERTY_COPYQUEUE = Ghurund::ReadOnlyProperty<Graphics, ID3D12CommandQueue*>("CopyQueue", (ID3D12CommandQueue * (Graphics::*)()) & getCopyQueue);
        static auto PROPERTY_FACTORY = Ghurund::ReadOnlyProperty<Graphics, IDXGIFactory4*>("Factory", (IDXGIFactory4 * (Graphics::*)()) & getFactory);
        static auto PROPERTY_DESCRIPTORALLOCATOR = Ghurund::ReadOnlyProperty<Graphics, Ghurund::DescriptorAllocator&>("DescriptorAllocator", (Ghurund::DescriptorAllocator & (Graphics::*)()) & getDescriptorAllocator);
        static auto PROPERTY_RESOURCEFACTORY = Ghurund::ReadOnlyProperty<Graphics, GPUResourceFactory&>("ResourceFactory", (GPUResourceFactory & (Graphics::*)()) & getResourceFactory);

        static const auto CONSTRUCTOR = Constructor<Graphics>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Graphics>("Ghurund", "Graphics")
            .withProperty(PROPERTY_DEVICE)
            .withProperty(PROPERTY_DIRECTQUEUE)
            .withProperty(PROPERTY_COMPUTEQUEUE)
            .withProperty(PROPERTY_COPYQUEUE)
            .withProperty(PROPERTY_FACTORY)
            .withProperty(PROPERTY_DESCRIPTORALLOCATOR)
            .withProperty(PROPERTY_RESOURCEFACTORY)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Status Graphics::initAdapters() {
        ComPtr<IDXGIAdapter1> adapter;

        unsigned int adapterIndex = 0;
        while (true) {
            if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter))
                break;

            adapters.add(ghnew GraphicsAdapter(adapter));
            adapterIndex++;
        }

        if (FAILED(factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("factory->EnumWarpAdapter() failed\n"));

        adapters.add(ghnew GraphicsAdapter(adapter));

        return adapters.Size > 0 ? Status::OK : Status::DIRECTX12_NOT_SUPPORTED;
    }

    Status Graphics::init() {
        UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
            debugController->EnableDebugLayer();

            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
#endif

        if (FAILED(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)))) {
            Logger::log(LogType::ERR0R, _T("failed to create DXGIFactory2"));
            return Status::CALL_FAIL;
        }

        return initAdapters();
    }

    Status Graphics::initDevice(GraphicsAdapter& adapter) {
        if (FAILED(D3D12CreateDevice(adapter.get().Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("D3D12CreateDevice failed\n"));

        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

        if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&directQueue))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("create direct queue failed\n"));
        directQueue->SetName(L"direct queue");

        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;

        if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&computeQueue))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("create compute queue failed\n"));
        computeQueue->SetName(L"compute queue");

        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;

        if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&copyQueue))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("create copy queue failed\n"));
        copyQueue->SetName(L"copy queue");

        /*if(FAILED(factory->MakeWindowAssociation(window.Handle, DXGI_MWA_NO_ALT_ENTER))) {
            Logger::log(_T("factory->MakeWindowAssociation() failed\n"));
            return Status::CALL_FAIL;
        }*/

        // TODO: do it properly
        allocator.allocate(*this, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        allocator.allocate(*this, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

        resourceFactory = ghnew GPUResourceFactory(*this);

        return Status::OK;
    }

    void Graphics::uninitDevice() {
        directQueue->Release();
        directQueue = nullptr;
        computeQueue->Release();
        computeQueue = nullptr;
        copyQueue->Release();
        copyQueue = nullptr;
        delete resourceFactory;
        resourceFactory = nullptr;
        device->Release();
        device = nullptr;
    }

    void Graphics::uninit() {
        adapters.deleteItems();
        factory->Release();
        factory = nullptr;
    }

}