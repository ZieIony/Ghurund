#include "ghedxpch.h"
#include "DxGraphics.h"

#include "core/exception/Exceptions.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/logging/Logger.h"
#include "DirectXTypes.h"
#include "shader/DxShaderLoader.h"
#include "material/DxMaterialLoader.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& DxGraphics::GET_TYPE() {
        static auto PROPERTY_DEVICE = Property<DxGraphics, ID3D12Device*>("Device", &getDevice);
        static auto PROPERTY_DIRECTQUEUE = Property<DxGraphics, ID3D12CommandQueue*>("DirectQueue", &getDirectQueue);
        static auto PROPERTY_COMPUTEQUEUE = Property<DxGraphics, ID3D12CommandQueue*>("ComputeQueue", &getComputeQueue);
        static auto PROPERTY_COPYQUEUE = Property<DxGraphics, ID3D12CommandQueue*>("CopyQueue", &getCopyQueue);
        static auto PROPERTY_FACTORY = Property<DxGraphics, IDXGIFactory4*>("Factory", &getFactory);
        static auto PROPERTY_DESCRIPTORALLOCATOR = Property<DxGraphics, Ghurund::Engine::DirectX::DescriptorAllocator&>("DescriptorAllocator", &getDescriptorAllocator);
        static auto PROPERTY_RESOURCEFACTORY = Property<DxGraphics, GPUResourceFactory&>("ResourceFactory", &getResourceFactory);

        static const Ghurund::Core::Type TYPE = TypeBuilder<DxGraphics>()
            .withProperty(PROPERTY_DEVICE)
            .withProperty(PROPERTY_DIRECTQUEUE)
            .withProperty(PROPERTY_COMPUTEQUEUE)
            .withProperty(PROPERTY_COPYQUEUE)
            .withProperty(PROPERTY_FACTORY)
            .withProperty(PROPERTY_DESCRIPTORALLOCATOR)
            .withProperty(PROPERTY_RESOURCEFACTORY)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxGraphics::initAdapters() {
        ComPtr<IDXGIAdapter1> adapter;

        unsigned int adapterIndex = 0;
        while (true) {
            if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter))
                break;

            auto graphicsAdapter = ghnew GraphicsAdapter(adapter);
            if (graphicsAdapter->Outputs.Empty) {
                delete graphicsAdapter;
            } else {
                adapters.add(graphicsAdapter);
            }
            adapterIndex++;
        }

        if (FAILED(factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter))))
            Logger::log(LogType::WARNING, _T("factory->EnumWarpAdapter() failed\n"));

        auto graphicsAdapter = ghnew GraphicsAdapter(adapter);
        if (graphicsAdapter->Outputs.Empty) {
            delete graphicsAdapter;
        } else {
            adapters.add(graphicsAdapter);
        }

        if (adapters.Empty)
            throw DirectX12NotSupportedException();
    }

    void DxGraphics::uninitGraphics() {
        uninitDevice();
        adapters.deleteItems();
        factory->Release();
        factory = nullptr;
    }

    void DxGraphics::onInit() {
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

    void DxGraphics::initDevice(GraphicsAdapter& adapter) {
        if (FAILED(D3D12CreateDevice(adapter.get().Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device)))) {
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

    void DxGraphics::uninitDevice() {
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

    void DxGraphics::onUninit() {
        uninitGraphics();
    }

}