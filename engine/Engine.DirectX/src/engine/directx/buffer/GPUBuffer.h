#pragma once

#include "core/Buffer.h"
#include "core/object/RefCountedObject.h"
#include "engine/directx/CommandList.h"

namespace Ghurund::Engine::DirectX {
    class GPUBuffer {
    private:
        ID3D12Resource *constantBufferUploadHeap = nullptr; // this is the memory on the gpu where our constant buffer will be placed.
        RefCountedObject* resourcePointer = nullptr;
        Buffer *buffer = nullptr;
		void *gpuAddress = nullptr;

        //GraphicsMemory *memory;

        GPUBuffer(const GPUBuffer& other) = delete;

    public:
        GPUBuffer() {}

        ~GPUBuffer() {
			uninit();
        }

        void init(DxGraphics& graphics, size_t size);

		void uninit();

        void setValue(const void *value) {
            memcpy(buffer->Data, value, buffer->Size);
        }

		void setValue(const void* value, size_t size, size_t offset) {
			memcpy((BYTE*)buffer->Data + offset, value, size);
		}

		template<class Type> void setValue(const Type& value, size_t offset) {
			memcpy((BYTE*)buffer->Data + offset, &value, sizeof(Type));
		}

        void set(CommandList& commandList, unsigned int bindSlot);
    };
}