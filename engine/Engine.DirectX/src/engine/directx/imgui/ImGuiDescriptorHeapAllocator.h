#pragma once

#include "core/collection/List.h"

#include <d3d12.h>

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class ImGuiDescriptorHeapAllocator {
    private:
		ID3D12DescriptorHeap* descriptorHeap = nullptr;
		D3D12_DESCRIPTOR_HEAP_TYPE heapType = D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES;
		D3D12_CPU_DESCRIPTOR_HANDLE heapStartCpu;
		D3D12_GPU_DESCRIPTOR_HANDLE heapStartGpu;
		UINT heapHandleIncrement;
		List<int> freeIndices;

    public:
        ~ImGuiDescriptorHeapAllocator() {
            deinit();
        }

        void init(ID3D12Device* device) {
            D3D12_DESCRIPTOR_HEAP_DESC desc = {};
            desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
            desc.NumDescriptors = 64;
            desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
            device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptorHeap));

            heapType = desc.Type;
            heapStartCpu = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
            heapStartGpu = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
            heapHandleIncrement = device->GetDescriptorHandleIncrementSize(heapType);
            freeIndices.resize((int)desc.NumDescriptors);
            for (int n = desc.NumDescriptors; n > 0; n--)
                freeIndices.add(n - 1);
        }

        void deinit() {
            if (descriptorHeap) {
                descriptorHeap->Release();
                descriptorHeap = nullptr;
            }
            freeIndices.clear();
        }

        inline ID3D12DescriptorHeap* getHeap() const {
            return descriptorHeap;
        }

        void alloc(D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_desc_handle) {
            _ASSERTE(freeIndices.Size > 0);
            int idx = *freeIndices.rbegin();
			freeIndices.removeAt(freeIndices.Size - 1);
            out_cpu_desc_handle->ptr = heapStartCpu.ptr + (idx * heapHandleIncrement);
            out_gpu_desc_handle->ptr = heapStartGpu.ptr + (idx * heapHandleIncrement);
        }

        void free(D3D12_CPU_DESCRIPTOR_HANDLE out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE out_gpu_desc_handle) {
            int cpu_idx = (int)((out_cpu_desc_handle.ptr - heapStartCpu.ptr) / heapHandleIncrement);
            int gpu_idx = (int)((out_gpu_desc_handle.ptr - heapStartGpu.ptr) / heapHandleIncrement);
            _ASSERTE(cpu_idx == gpu_idx);
            freeIndices.add(cpu_idx);
        }
    };
}
