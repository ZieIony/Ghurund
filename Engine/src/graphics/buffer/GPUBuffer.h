#pragma once

#include "graphics/Graphics.h"
#include "collection/BufferedValue.h"
#include "graphics/CommandList.h"

namespace Ghurund {
    class GPUBuffer {
    private:
		DescriptorHandle descHandle;
        ComPtr<ID3D12Resource> constantBufferUploadHeap; // this is the memory on the gpu where our constant buffer will be placed.
        void *data = nullptr;
        size_t size;
		void *gpuAddress;

    public:
        ~GPUBuffer() {
			uninit();
        }

        void init(Graphics &graphics, size_t size) {
            descHandle = graphics.DescriptorAllocator.allocate(graphics, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

            graphics.getDevice()->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(1024 * 64), // size of the resource heap. Must be a multiple of 64KB for single-textures and constant buffers	// TODO: compute actual heap size
                D3D12_RESOURCE_STATE_GENERIC_READ, // will be data that is read from so we keep it in the generic read state
                nullptr,
                IID_PPV_ARGS(&constantBufferUploadHeap));

            D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
            cbvDesc.BufferLocation = constantBufferUploadHeap->GetGPUVirtualAddress();
            cbvDesc.SizeInBytes = align<unsigned int>(size, 256);    // CB size is required to be 256-byte aligned.
            graphics.getDevice()->CreateConstantBufferView(&cbvDesc, descHandle.getCpuHandle());

            data = ghnew BYTE[size];
            ZeroMemory(data, size);
            this->size = size;

            CD3DX12_RANGE readRange(0, 0);
            constantBufferUploadHeap->Map(0, &readRange, (void**)&gpuAddress);
            memcpy(gpuAddress, data, size);
        }

		void uninit() {
			if (constantBufferUploadHeap) {
				constantBufferUploadHeap->Unmap(0, nullptr);
				constantBufferUploadHeap.Reset();
			}
			delete[] data;
		}

        void setValue(const void *value) {
            memcpy(data, value, size);
        }

        void setValue(const void *value, size_t size, size_t offset) {
            memcpy((BYTE*)data+offset, value, size);
        }

        void set(CommandList &commandList, unsigned int bindSlot) {
            memcpy(gpuAddress, data, size);

            commandList.get()->SetGraphicsRootDescriptorTable(bindSlot, descHandle.getGpuHandle());
        }

    };
}