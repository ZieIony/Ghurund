#pragma once

#include "Common.h"

#include <stdint.h>
#include <memory.h>
#include <utility>

namespace Ghurund::Core {
    class Buffer {
    private:
        uint8_t* data;
        size_t size;

    public:
        Buffer() {
            data = nullptr;
            size = 0;
        }

        Buffer(size_t size) {
            data = ghnew uint8_t[size];
            this->size = size;
        }

        Buffer(const void* data, size_t size) {
            this->data = ghnew uint8_t[size];
            this->size = size;
            memcpy(this->data, data, size);
        }

        Buffer(const Buffer& other) {
            data = ghnew uint8_t[other.size];
            size = other.size;
            memcpy(data, other.data, size);
        }

        Buffer(Buffer&& other) noexcept {
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
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

        inline void setData(const void* data, size_t size) {
            if (size != this->size) {
                delete[] this->data;
                this->size = size;
                this->data = ghnew uint8_t[size];
            }
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
            other.data = nullptr;
            other.size = 0;

            return *this;
        }

        inline void resize(size_t size) {
            if (size) {
                uint8_t* prev = data;
                data = ghnew uint8_t[size];
                if (prev) {
                    memcpy(data, prev, std::min(this->size, size));
                    delete[] prev;
                }
            } else {
                delete[] data;
                data = nullptr;
            }
            this->size = std::min(this->size, size);
        }

        inline void zero() {
            memset(data, 0, size);
        }
    };
}