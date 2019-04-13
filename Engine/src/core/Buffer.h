#pragma once

#include "ghurund.h"

namespace Ghurund {
    class Buffer {
    private:
        BYTE *data;
        size_t size;

    public:
        Buffer(size_t size) {
            data = ghnew BYTE[size];
            this->size = size;
        }

        Buffer(const void *data, size_t size) {
            this->data = ghnew BYTE[size];
            this->size = size;
            memcpy(this->data, data, size);
        }

        Buffer(const Buffer &buffer) {
            data = ghnew BYTE[buffer.size];
            size = buffer.size;
            memcpy(data, buffer.data, size);
        }

        ~Buffer() {
            delete[] data;
        }

        BYTE *getData() {
            return data;
        }

        __declspec(property(get = getData)) BYTE *Data;

        size_t getSize() {
            return size;
        }
      
        __declspec(property(get = getSize)) size_t Size;

        void zero() {
            memset(data, 0, size);
        }
    };
}