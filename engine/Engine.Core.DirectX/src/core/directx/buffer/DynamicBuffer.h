#pragma once

#include "core/directx/Graphics.h"
#include "core/collection/BufferedValue.h"
#include "GPUBuffer.h"

namespace Ghurund::Core::DirectX {
    class DynamicBuffer {
    private:
        GPUBuffer *buffers = nullptr;
        BufferedValue<GPUBuffer> bufferedValue;

    public:
        ~DynamicBuffer() {
            delete[] buffers;
        }

        void init(Graphics &graphics, size_t size) {
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
            //bufferedValue->set(commandList, bindSlot);
            bufferedValue.next();
        }
    };
}