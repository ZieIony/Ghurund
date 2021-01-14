#pragma once

#include "Common.h"

#include <memory.h>

namespace Ghurund {
    class Buffer {
    private:
        uint8_t *data;
        size_t size;

    public:
        Buffer(size_t size) {
            data = ghnew uint8_t[size];
            this->size = size;
        }

        Buffer(const void *data, size_t size) {
            this->data = ghnew uint8_t[size];
            this->size = size;
            memcpy(this->data, data, size);
        }

        Buffer(const Buffer &buffer) {
            data = ghnew uint8_t[buffer.size];
            size = buffer.size;
            memcpy(data, buffer.data, size);
        }

        ~Buffer() {
            delete[] data;
        }

        uint8_t* getData() {
            return data;
        }

        const uint8_t* getData() const {
            return data;
        }

        __declspec(property(get = getData)) uint8_t *Data;

        size_t getSize() const {
            return size;
        }
      
        __declspec(property(get = getSize)) size_t Size;

        void zero() {
            memset(data, 0, size);
        }
    };
}