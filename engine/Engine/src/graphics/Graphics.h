#pragma once

#include "core/Object.h"
#include "core/collection/List.h"
#include "core/reflection/Type.h"
#include "graphics/adapter/GraphicsAdapter.h"
#include "graphics/buffer/DescriptorHeap.h"
#include "graphics/memory/GPUResourceFactory.h"

namespace Ghurund {
    using namespace DirectX;
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class CommandList;

    class Graphics: public Object {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        ID3D12Device* device;
        ID3D12CommandQueue* directQueue = nullptr, * computeQueue = nullptr, * copyQueue = nullptr;
        IDXGIFactory4* factory;

        DescriptorAllocator allocator;
        GPUResourceFactory* resourceFactory;

        List<GraphicsAdapter*> adapters;

        Status initAdapters();

    public:
        ~Graphics() {
            uninitDevice();
            uninit();
        }

        Status init();
        Status initDevice(GraphicsAdapter& adapter);

        void uninitDevice();
        void uninit();

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

        __declspec(property(get = getDescriptorAllocator)) Ghurund::DescriptorAllocator& DescriptorAllocator;

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