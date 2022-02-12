#pragma once

#include "core/Object.h"
#include "core/collection/List.h"
#include "core/reflection/Type.h"
#include "core/directx/adapter/GraphicsAdapter.h"
#include "core/directx/buffer/DescriptorHeap.h"
#include "core/directx/memory/GPUResourceFactory.h"
#include "core/application/Feature.h"

namespace Ghurund::Core::DirectX {
    using namespace DirectX;
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class CommandList;

    class Graphics: public Ghurund::Core::Feature {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
#pragma endregion

    private:
        ID3D12Device* device;
        ID3D12CommandQueue* directQueue = nullptr, * computeQueue = nullptr, * copyQueue = nullptr;
        IDXGIFactory4* factory;

        DescriptorAllocator allocator;
        GPUResourceFactory* resourceFactory;

        List<GraphicsAdapter*> adapters;

        void initAdapters();

    public:
        ~Graphics() {
            uninit();
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

        List<GraphicsAdapter*>& getAdapters() {
            return adapters;
        }

        __declspec(property(get = getAdapters)) List<GraphicsAdapter*>& Adapters;

        DescriptorAllocator& getDescriptorAllocator() {
            return allocator;
        }

        __declspec(property(get = getDescriptorAllocator)) Ghurund::Core::DirectX::DescriptorAllocator& DescriptorAllocator;

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