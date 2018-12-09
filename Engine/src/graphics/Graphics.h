#pragma once

#include "Ghurund.h"

#include "collection/List.h"
#include "core/Logger.h"
#include "core/Object.h"
#include "graphics/Adapter.h"
#include "graphics/buffer/DescriptorHeap.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    class CommandList;

    class Graphics: public Object {
    private:
        ComPtr<ID3D12Device> device;
        ComPtr<ID3D12CommandQueue> directQueue, computeQueue, copyQueue;
        ComPtr<IDXGIFactory4> factory;

		DescriptorAllocator allocator;

        List<Adapter*> adapters;

        Status initAdapters();

    public:

        ~Graphics() {
            uninit();
        }

        Status init();

        void uninit() {
            adapters.deleteItems();
        }

        ComPtr<ID3D12Device> getDevice() {
            return device;
        }

        __declspec(property(get = getDevice)) ComPtr<ID3D12Device> Device;

        ComPtr<ID3D12CommandQueue> getDirectQueue() {
            return directQueue;
        }

        __declspec(property(get = getDirectQueue)) ComPtr<ID3D12CommandQueue> DirectQueue;

        ComPtr<ID3D12CommandQueue> getComputeQueue() {
            return computeQueue;
        }

        __declspec(property(get = getComputeQueue)) ComPtr<ID3D12CommandQueue> ComputeQueue;

        ComPtr<ID3D12CommandQueue> getCopyQueue() {
            return copyQueue;
        }

        __declspec(property(get = CopyQueue)) ComPtr<ID3D12CommandQueue> CopyQueue;

        ComPtr<IDXGIFactory4> getFactory() {
            return factory;
        }

        __declspec(property(get = getFactory)) ComPtr<IDXGIFactory4> Factory;

        List<Adapter*> &getAdapters() {
            return adapters;
        }

        __declspec(property(get = getAdapters)) List<Adapter*> &Adapters;

		DescriptorAllocator &getDescriptorAllocator() {
			return allocator;
		}

		__declspec(property(get = getDescriptorAllocator)) DescriptorAllocator &DescriptorAllocator;
    };
}