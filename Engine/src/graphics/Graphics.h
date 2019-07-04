#pragma once

#include "collection/List.h"
#include "core/Logger.h"
#include "core/Object.h"
#include "graphics/Adapter.h"
#include "graphics/buffer/DescriptorHeap.h"
#include "graphics/memory/GPUResourceFactory.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <wrl.h>

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

        List<Adapter*> adapters;

        Status initAdapters();

    public:

        ~Graphics() {
            uninit();
        }

        Status init();

        void uninit() {
            adapters.deleteItems();
            directQueue->Release();
            computeQueue->Release();
            copyQueue->Release();
            delete resourceFactory;
            factory->Release();
            device->Release();
        }

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

        List<Adapter*>& getAdapters() {
            return adapters;
        }

        __declspec(property(get = getAdapters)) List<Adapter*>& Adapters;

        DescriptorAllocator& getDescriptorAllocator() {
            return allocator;
        }

        __declspec(property(get = getDescriptorAllocator)) DescriptorAllocator& DescriptorAllocator;

        GPUResourceFactory& getResourceFactory() {
            return *resourceFactory;
        }

        __declspec(property(get = getResourceFactory)) GPUResourceFactory& ResourceFactory;

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}