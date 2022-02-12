#include "ghcdxpch.h"
#include "Graphics.h"

#include "Exceptions.h"
#include "core/Exceptions.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/ReadOnlyProperty.h"
#include "DirectXTypes.h"
#include "core/logging/Logger.h"

#include <D3Dcompiler.h>

namespace Ghurund::Core::DirectX {
    const Ghurund::Core::Type& Graphics::GET_TYPE() {
        static auto PROPERTY_DEVICE = Ghurund::Core::ReadOnlyProperty<Graphics, ID3D12Device*>("Device", (ID3D12Device * (Graphics::*)()) & getDevice);
        static auto PROPERTY_DIRECTQUEUE = Ghurund::Core::ReadOnlyProperty<Graphics, ID3D12CommandQueue*>("DirectQueue", (ID3D12CommandQueue * (Graphics::*)()) & getDirectQueue);
        static auto PROPERTY_COMPUTEQUEUE = Ghurund::Core::ReadOnlyProperty<Graphics, ID3D12CommandQueue*>("ComputeQueue", (ID3D12CommandQueue * (Graphics::*)()) & getComputeQueue);
        static auto PROPERTY_COPYQUEUE = Ghurund::Core::ReadOnlyProperty<Graphics, ID3D12CommandQueue*>("CopyQueue", (ID3D12CommandQueue * (Graphics::*)()) & getCopyQueue);
        static auto PROPERTY_FACTORY = Ghurund::Core::ReadOnlyProperty<Graphics, IDXGIFactory4*>("Factory", (IDXGIFactory4 * (Graphics::*)()) & getFactory);
        static auto PROPERTY_DESCRIPTORALLOCATOR = Ghurund::Core::ReadOnlyProperty<Graphics, Ghurund::Core::DirectX::DescriptorAllocator&>("DescriptorAllocator", (Ghurund::Core::DirectX::DescriptorAllocator & (Graphics::*)()) & getDescriptorAllocator);
        static auto PROPERTY_RESOURCEFACTORY = Ghurund::Core::ReadOnlyProperty<Graphics, GPUResourceFactory&>("ResourceFactory", (GPUResourceFactory & (Graphics::*)()) & getResourceFactory);

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

    void Graphics::initAdapters() {
        ComPtr<IDXGIAdapter1> adapter;

        unsigned int adapterIndex = 0;
        while (true) {
            if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter))
                break;

            adapters.add(ghnew GraphicsAdapter(adapter));
            adapterIndex++;
        }

        if (FAILED(factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter))))
            Logger::log(LogType::WARNING, _T("factory->EnumWarpAdapter() failed\n"));

        adapters.add(ghnew GraphicsAdapter(adapter));

        if (adapters.Empty)
            throw DirectX12NotSupportedException();
    }

    void Graphics::onInit() {
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
            throw CallFailedException();
        }

        initAdapters();
        initDevice(*adapters[0]);
    }

    void Graphics::initDevice(GraphicsAdapter& adapter) {
        if (FAILED(D3D12CreateDevice(adapter.get().Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)))) {
            Logger::log(LogType::ERR0R, _T("D3D12CreateDevice failed\n"));
            throw CallFailedException();
        }

        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

        if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&directQueue)))) {
            Logger::log(LogType::ERR0R, _T("create direct queue failed\n"));
            throw CallFailedException();
        }
        directQueue->SetName(L"direct queue");

        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;

        if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&computeQueue)))) {
            Logger::log(LogType::ERR0R, _T("create compute queue failed\n"));
            throw CallFailedException();
        }
        computeQueue->SetName(L"compute queue");

        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;

        if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&copyQueue)))) {
            Logger::log(LogType::ERR0R, _T("create copy queue failed\n"));
            throw CallFailedException();
        }
        copyQueue->SetName(L"copy queue");

        /*if(FAILED(factory->MakeWindowAssociation(window.Handle, DXGI_MWA_NO_ALT_ENTER))) {
            Logger::log(_T("factory->MakeWindowAssociation() failed\n"));
            return Status::CALL_FAIL;
        }*/

        // TODO: do it properly
        allocator.allocate(*this, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        allocator.allocate(*this, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

        resourceFactory = ghnew GPUResourceFactory(*this);
    }

    void Graphics::uninitDevice() {
        if (directQueue) {
            directQueue->Release();
            directQueue = nullptr;
        }
        if (computeQueue) {
            computeQueue->Release();
            computeQueue = nullptr;
        }
        if (copyQueue) {
            copyQueue->Release();
            copyQueue = nullptr;
        }
        delete resourceFactory;
        resourceFactory = nullptr;
        if (device) {
            device->Release();
            device = nullptr;
        }
    }

    void Graphics::onUninit() {
        uninitDevice();
        adapters.deleteItems();
        factory->Release();
        factory = nullptr;
    }

}