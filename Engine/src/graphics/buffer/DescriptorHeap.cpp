#include "DescriptorHeap.h"
#include "graphics/Graphics.h"

namespace Ghurund {

	Status DescriptorHeap::init(Graphics &graphics){
		if (FAILED(graphics.Device->CreateDescriptorHeap(&heapDescriptor, IID_PPV_ARGS(heap.ReleaseAndGetAddressOf())))) {
			Logger::log(_T("CreateDescriptorHeap(...) failed\n"));
			return Status::CALL_FAIL;
		}

		descriptorSize = graphics.Device->GetDescriptorHandleIncrementSize(heapDescriptor.Type);
		numFreeDescriptors = heapDescriptor.NumDescriptors;
		firstHandle = DescriptorHandle(heap->GetCPUDescriptorHandleForHeapStart(), heap->GetGPUDescriptorHandleForHeapStart());
		nextFreeHandle = firstHandle;

		return Status::OK;
	}

	DescriptorHandle DescriptorHeap::allocate(){
		if (!hasAvailableSpace()) {
			//"Descriptor Heap out of space.  Increase heap size.");
		}
		DescriptorHandle ret = nextFreeHandle;
		nextFreeHandle += descriptorSize;
		return ret;
	}

	bool DescriptorHeap::validateHandle(const DescriptorHandle& handle) const{
		if (handle.getCpuHandle().ptr < firstHandle.getCpuHandle().ptr ||
			handle.getCpuHandle().ptr >= firstHandle.getCpuHandle().ptr + heapDescriptor.NumDescriptors * descriptorSize)
			return false;

		if (handle.getGpuHandle().ptr - firstHandle.getGpuHandle().ptr !=
			handle.getCpuHandle().ptr - firstHandle.getCpuHandle().ptr)
			return false;

		return true;
	}
}