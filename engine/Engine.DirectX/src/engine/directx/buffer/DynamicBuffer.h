#pragma once

#include "GPUBuffer.h"

#include "core/collection/BufferedValue.h"
#include "engine/directx/CommandList.h"
#include "engine/directx/DxGraphics.h"

namespace Ghurund::Engine::DirectX {
    class DynamicBuffer {
    private:
        GPUBuffer *buffers = nullptr;
        BufferedValue<GPUBuffer> bufferedValue;

    public:
        ~DynamicBuffer() {
            delete[] buffers;
        }

        void init(DxGraphics &graphics, size_t size) {
            buffers = ghnew GPUBuffer[2];
            buffers[0].init(graphics, size);
            buffers[1].init(graphics, size);
            bufferedValue.init(buffers, 2);
        }

        void setValue(const void *value) {
            bufferedValue->setValue(value);
        }

        void setValue(const void *value, size_t size, size_t offset) {
            bufferedValue->setValue(value, size, offset);
        }

        void set(CommandList &commandList, unsigned int bindSlot) {
            //bufferedValue->apply(commandList, bindSlot);
            bufferedValue.next();
        }
    };
}