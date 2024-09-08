#include "ghedxpch.h"
#include "DescriptorHeap.h"

#include "engine/directx/Graphics.h"
#include "core/logging/Logger.h"

namespace Ghurund::Engine::DirectX {

	void DescriptorHeap::init(Graphics &graphics){
		if (FAILED(graphics.Device->CreateDescriptorHeap(&heapDescriptor, IID_PPV_ARGS(&heap)))) {
			return Logger::log(LogType::ERR0R, _T("CreateDescriptorHeap(...) failed\n"));
			throw CallFailedException();
		}

		descriptorSize = graphics.Device->GetDescriptorHandleIncrementSize(heapDescriptor.Type);
		numFreeDescriptors = heapDescriptor.NumDescriptors;
        cpuDescriptorHandleForHeapStart = heap->GetCPUDescriptorHandleForHeapStart();
        gpuDescriptorHandleForHeapStart = heap->GetGPUDescriptorHandleForHeapStart();
	}

	DescriptorHandle DescriptorHeap::allocate(){
		if (!hasAvailableSpace()) {
			//"Descriptor Heap out of space.  Increase heap size.");
		}
		DescriptorHandle ret = DescriptorHandle(cpuDescriptorHandleForHeapStart.ptr + nextFreeHandle * descriptorSize, gpuDescriptorHandleForHeapStart.ptr + nextFreeHandle * descriptorSize);
		nextFreeHandle ++;
		return ret;
	}

}