#include "DescriptorHeap.h"
#include "graphics/Graphics.h"

namespace Ghurund {

	Status DescriptorHeap::init(Graphics &graphics){
		if (FAILED(graphics.Device->CreateDescriptorHeap(&heapDescriptor, IID_PPV_ARGS(&heap)))) {
			Logger::log(_T("CreateDescriptorHeap(...) failed\n"));
			return Status::CALL_FAIL;
		}

		descriptorSize = graphics.Device->GetDescriptorHandleIncrementSize(heapDescriptor.Type);
		numFreeDescriptors = heapDescriptor.NumDescriptors;
        cpuDescriptorHandleForHeapStart = heap->GetCPUDescriptorHandleForHeapStart();
        gpuDescriptorHandleForHeapStart = heap->GetGPUDescriptorHandleForHeapStart();

		return Status::OK;
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