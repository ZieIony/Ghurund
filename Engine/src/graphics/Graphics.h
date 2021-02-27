#pragma once

#include "core/collection/List.h"
#include "core/Object.h"
#include "graphics/GraphicsAdapter.h"
#include "graphics/buffer/DescriptorHeap.h"
#include "graphics/memory/GPUResourceFactory.h"

namespace Ghurund {
    using namespace DirectX;
    using namespace Microsoft::WRL;

    class CommandList;

    class Graphics: public Object {
    private:
        ID3D12Device* device;
        ID3D12CommandQueue* directQueue = nullptr, * computeQueue = nullptr, * copyQueue = nullptr;
        IDXGIFactory4* factory;

        DescriptorAllocator allocator;
        GPUResourceFactory* resourceFactory;

        List<GraphicsAdapter*> adapters;

        Status initAdapters();

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        ~Graphics() {
            uninit();
        }

        Status init();

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

        __declspec(property(get = getDescriptorAllocator)) DescriptorAllocator& DescriptorAllocator;

        GPUResourceFactory& getResourceFactory() {
            return *resourceFactory;
        }

        __declspec(property(get = getResourceFactory)) GPUResourceFactory& ResourceFactory;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}