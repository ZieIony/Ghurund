#pragma once

#include "core/object/Object.h"
#include "core/collection/List.h"
#include "core/reflection/Type.h"
#include "engine/directx/adapter/GraphicsAdapter.h"
#include "engine/directx/buffer/DescriptorHeap.h"
#include "engine/directx/memory/GPUResourceFactory.h"
#include "core/feature/Feature.h"

namespace Ghurund::Engine::DirectX {
    using namespace DirectX;
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class CommandList;

    class DxGraphics: public Ghurund::Core::Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxGraphics::GET_TYPE();
#pragma endregion

    private:
        ID3D12Device* device;
        ID3D12CommandQueue* directQueue = nullptr, * computeQueue = nullptr, * copyQueue = nullptr;
        IDXGIFactory4* factory;

        DescriptorAllocator allocator;
        GPUResourceFactory* resourceFactory;

        List<GraphicsAdapter*> adapters;

        void initAdapters();

        void uninitGraphics();

    public:
        ~DxGraphics() {
            if(IsInitialized)
                uninitGraphics();
        }

        virtual void onInit() override;
        void initDevice(GraphicsAdapter& adapter);

        virtual void onUninit() override;
        void uninitDevice();

        ID3D12Device* getDevice() {
            return device;
        }

        __declspec(property(get = getDevice)) ID3D12Device* Device;

        ID3D12CommandQueue* getDirectQueue() {
            return directQueue;
        }

        __declspec(property(get = getDirectQueue)) ID3D12CommandQueue* DirectQueue;

        ID3D12CommandQueue* getComputeQueue() {
            return computeQueue;
        }

        __declspec(property(get = getComputeQueue)) ID3D12CommandQueue* ComputeQueue;

        ID3D12CommandQueue* getCopyQueue() {
            return copyQueue;
        }

        __declspec(property(get = getCopyQueue)) ID3D12CommandQueue* CopyQueue;

        IDXGIFactory4* getFactory() {
            return factory;
        }

        __declspec(property(get = getFactory)) IDXGIFactory4* Factory;

        const List<GraphicsAdapter*>& getAdapters() const {
            return adapters;
        }

        __declspec(property(get = getAdapters)) const List<GraphicsAdapter*>& Adapters;

        DescriptorAllocator& getDescriptorAllocator() {
            return allocator;
        }

        __declspec(property(get = getDescriptorAllocator)) Ghurund::Engine::DirectX::DescriptorAllocator& DescriptorAllocator;

        GPUResourceFactory& getResourceFactory() {
            return *resourceFactory;
        }

        __declspec(property(get = getResourceFactory)) GPUResourceFactory& ResourceFactory;
    };

    template<typename T>
    ULONG getRefCount(T& object) {
        object.AddRef();
        return object.Release();
    }
}