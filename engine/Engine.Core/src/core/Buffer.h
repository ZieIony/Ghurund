#pragma once

#include "Common.h"

#include <stdint.h>
#include <memory.h>
#include <utility>

namespace Ghurund::Core {
    class Buffer {
    private:
        uint8_t* data;
        size_t size, capacity;

    public:
        Buffer() {
            data = nullptr;
            size = 0;
            capacity = 0;
        }

        Buffer(size_t capacity) {
            data = ghnew uint8_t[capacity];
            this->size = 0;
            this->capacity = capacity;
        }

        Buffer(const void* data, size_t size) {
            this->data = ghnew uint8_t[size];
            this->size = size;
            this->capacity = size;
            memcpy(this->data, data, size);
        }

        Buffer(const Buffer& other) {
            data = ghnew uint8_t[other.size];
            size = other.size;
            capacity = other.capacity;
            memcpy(data, other.data, size);
        }

        Buffer(Buffer&& other) noexcept {
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        ~Buffer() {
            delete[] data;
        }

        inline uint8_t* getData() {
            return data;
        }

        inline const uint8_t* getData() const {
            return data;
        }

        __declspec(property(get = getData)) uint8_t* Data;

        inline size_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline size_t getCapacity() const {
            return capacity;
        }

        __declspec(property(get = getCapacity)) size_t Capacity;

        inline void setData(const void* data, size_t size) {
            if (size > capacity) {
                delete[] this->data;
                this->capacity = size;
                this->data = ghnew uint8_t[size];
            }
            this->size = size;
            memcpy(this->data, data, size);
        }

        inline Buffer& operator=(const Buffer& other) {
            if (this == &other)
                return *this;

            setData(other.data, other.size);

            return *this;
        }

        inline Buffer& operator=(Buffer&& other) noexcept {
            if (this == &other)
                return *this;

            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;

            return *this;
        }

        inline void resize(size_t capacity) {
            this->capacity = capacity;
            if (capacity) {
                uint8_t* prev = data;
                data = ghnew uint8_t[capacity];
                if (prev) {
                    memcpy(data, prev, std::min(capacity, size));
                    delete[] prev;
                }
            } else {
                delete[] data;
                data = nullptr;
            }
            size = std::min(capacity, size);
        }

        inline void reset(size_t capacity) {
            delete[] data;
            this->capacity = capacity;
            if (capacity) {
                data = ghnew uint8_t[capacity];
            } else {
                data = nullptr;
            }
            size = 0;
        }

        inline void zero() {
            memset(data, 0, capacity);
            size = 0;
        }
    };
}