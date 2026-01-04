#pragma once

#include "core/Buffer.h"
#include "core/object/RefCountedObject.h"
#include "engine/directx/CommandList.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"
#include "engine/graphics/shader/ConstantBuffer.h"

namespace Ghurund::Engine::DirectX {
    class DxConstantBuffer:public ConstantBuffer {
    private:
        ID3D12Resource *constantBufferUploadHeap = nullptr; // this is the memory on the gpu where our constant buffer will be placed.
        Buffer *buffer = nullptr;

        //GraphicsMemory *memory;

        DxConstantBuffer(const DxConstantBuffer& other) = delete;

    protected:
        ~DxConstantBuffer() {
            uninit();
        }

    public:
        DxConstantBuffer() {}

        void init(ComPtr<ID3D12Resource> uploadHeap);

		void uninit();

        virtual size_t getSize() const override {
            return buffer->Size;
        }

		virtual void setValue(const void* value, size_t size, size_t offset) override {
			memcpy((uint8_t*)buffer->Data + offset, value, size);
		}

        void set(CommandList& commandList, uint32_t bindSlot);
    };
}