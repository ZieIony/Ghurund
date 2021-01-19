#pragma once

#include "Common.h"

#include <memory.h>

namespace Ghurund {
    class Buffer {
    private:
        uint8_t *data;
        size_t size, capacity;

    public:
        Buffer(size_t capacity) {
            data = ghnew uint8_t[capacity];
            this->size = capacity;
            this->capacity = capacity;
        }

        Buffer(const void *data, size_t size) {
            this->data = ghnew uint8_t[size];
            this->size = size;
            this->capacity = size;
            memcpy(this->data, data, size);
        }

        Buffer(const Buffer &buffer) {
            data = ghnew uint8_t[buffer.size];
            size = buffer.size;
            capacity = buffer.capacity;
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

        void setSize(size_t size) {
            this->size = size;
        }

        __declspec(property(get = getSize, put = setSize)) size_t Size;

        size_t getCapacity() const {
            return capacity;
        }

        __declspec(property(get = getCapacity)) size_t Capacity;

        inline void setData(uint8_t* data, size_t size) {
            if (size > capacity) {
                delete[] this->data;
                this->capacity = size;
                this->data = ghnew uint8_t[size];
            }
            memcpy(this->data, data, size);
        }

        void zero() {
            memset(data, 0, capacity);
            size = 0;
        }
    };
}