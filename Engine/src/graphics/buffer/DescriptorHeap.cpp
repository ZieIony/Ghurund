#include "DescriptorHeap.h"
#include "graphics/Graphics.h"

namespace Ghurund {

	Status DescriptorHeap::init(Graphics &graphics){
		if (FAILED(graphics.Device->CreateDescriptorHeap(&heapDescriptor, IID_PPV_ARGS(&heap))))
			return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateDescriptorHeap(...) failed\n"));

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