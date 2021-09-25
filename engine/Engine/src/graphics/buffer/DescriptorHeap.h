#pragma once

#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/threading/CriticalSection.h"
#include "graphics/adapter/GraphicsAdapter.h"

#include <d3d12.h>

namespace Ghurund {
    using namespace Ghurund::Core;

    class Graphics;

    class DescriptorHandle {
    private:
        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
        D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;

    public:
        DescriptorHandle() {
			cpuHandle = {};
			gpuHandle = {};
		}	// TODO: this constructor 

        DescriptorHandle(SIZE_T cpuAddress, UINT64 gpuAddress) {
            cpuHandle.ptr = cpuAddress;
            gpuHandle.ptr = gpuAddress;
        }

        D3D12_CPU_DESCRIPTOR_HANDLE getCpuHandle() const {
            return cpuHandle;
        }

        __declspec(property(get = getCpuHandle)) D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle;

        D3D12_GPU_DESCRIPTOR_HANDLE getGpuHandle() const {
            return gpuHandle;
        }

        __declspec(property(get = getGpuHandle)) D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle;
    };

    class DescriptorHeap {
    private:
        ID3D12DescriptorHeap* heap = nullptr;
        D3D12_DESCRIPTOR_HEAP_DESC heapDescriptor;
        unsigned int descriptorSize = 0;
        unsigned int numFreeDescriptors = 0;
        D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorHandleForHeapStart;
        D3D12_GPU_DESCRIPTOR_HANDLE gpuDescriptorHandleForHeapStart;
        size_t nextFreeHandle = 0;

    public:
        DescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t descriptorCount) {
            heapDescriptor.Type = type;
            heapDescriptor.NumDescriptors = descriptorCount;
            heapDescriptor.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
            heapDescriptor.NodeMask = 1;

			cpuDescriptorHandleForHeapStart = {};
			gpuDescriptorHandleForHeapStart = {};
        }

        ~DescriptorHeap() {
            if (heap != nullptr)
                heap->Release();
        }

        Status init(Graphics& graphics);

        bool hasAvailableSpace() const { return numFreeDescriptors > 0; }
        DescriptorHandle allocate();

        ID3D12DescriptorHeap* get() const { return heap; }

    };

    class DescriptorAllocator {
    private:
        static const unsigned int numDescriptorsPerHeap = 256;

        Map<D3D12_DESCRIPTOR_HEAP_TYPE, DescriptorHeap*> heapMap;

    public:
        ~DescriptorAllocator() {
            for (size_t i = 0; i < heapMap.Size; i++)
                delete heapMap.getValue(i);
        }

        DescriptorHandle allocate(Graphics& graphics, D3D12_DESCRIPTOR_HEAP_TYPE type) {
            if (!heapMap.containsKey(type)) {
                auto dh = ghnew DescriptorHeap(type, numDescriptorsPerHeap);
                dh->init(graphics);
                heapMap.set(type, dh);
            }
            return heapMap.get(type)->allocate();
        }

        void set(ID3D12GraphicsCommandList* commandList) {
            ID3D12DescriptorHeap* heaps = {heapMap.getValue(0)->get()};
            commandList->SetDescriptorHeaps(1, &heaps);
        }
    };
}