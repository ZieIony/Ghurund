#pragma once

#include "Ghurund.h"
#include "core/CriticalSection.h"
#include "collection/List.h"
#include "core/Logger.h"
#include "graphics/Adapter.h"
#include "collection/Map.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
	class Graphics;

	class DescriptorHandle{
	private:
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;

	public:
		DescriptorHandle() {}	// TODO: this constructor 

		DescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle){
			this->cpuHandle = cpuHandle;
			this->gpuHandle = gpuHandle;
		}

		DescriptorHandle operator+ (int offsetScaledByDescriptorSize) const{
			DescriptorHandle ret = *this;
			ret += offsetScaledByDescriptorSize;
			return ret;
		}

		void operator += (int offsetScaledByDescriptorSize){
			cpuHandle.ptr += offsetScaledByDescriptorSize;
			gpuHandle.ptr += offsetScaledByDescriptorSize;
		}

		D3D12_CPU_DESCRIPTOR_HANDLE getCpuHandle() const {
			return cpuHandle;
		}

		D3D12_GPU_DESCRIPTOR_HANDLE getGpuHandle() const {
			return gpuHandle;
		}
	};

	class DescriptorHeap {
	private:
		ComPtr<ID3D12DescriptorHeap> heap;
		D3D12_DESCRIPTOR_HEAP_DESC heapDescriptor;
		unsigned int descriptorSize = 0;
		unsigned int numFreeDescriptors = 0;
		DescriptorHandle firstHandle;
		DescriptorHandle nextFreeHandle;

	public:
		DescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t descriptorCount){
			heapDescriptor.Type = type;
			heapDescriptor.NumDescriptors = descriptorCount;
			heapDescriptor.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			heapDescriptor.NodeMask = 1;
		}

		Status init(Graphics &graphics);

		bool hasAvailableSpace() const { return numFreeDescriptors>0; }
		DescriptorHandle allocate();

		DescriptorHandle getHandle(unsigned int index) const { return firstHandle + index * descriptorSize; }

		bool validateHandle(const DescriptorHandle& handle) const;

		ID3D12DescriptorHeap* getHeapPointer() const { return heap.Get(); }

	};

	class DescriptorAllocator {
	private:
		static const unsigned int numDescriptorsPerHeap = 256;

		Map<D3D12_DESCRIPTOR_HEAP_TYPE, DescriptorHeap*> heapMap;

	public:
		~DescriptorAllocator(){
			for (size_t i = 0; i < heapMap.Size; i++)
				delete heapMap.getValue(i);
		}

		DescriptorHandle allocate(Graphics &graphics, D3D12_DESCRIPTOR_HEAP_TYPE type) {
			if (!heapMap.contains(type)) {
				auto dh = ghnew DescriptorHeap(type, numDescriptorsPerHeap);
				dh->init(graphics);
				heapMap.set(type, dh);
			}
			return heapMap.get(type)->allocate();
		}

		void set(ID3D12GraphicsCommandList *commandList) {
			ID3D12DescriptorHeap *heaps = { heapMap.getValue(0)->getHeapPointer() };
			commandList->SetDescriptorHeaps(1, &heaps);
		}
	};
}