#pragma once

#include "Ghurund.h"
#include "Logger.h"
#include <algorithm>

namespace Ghurund {
    class MemoryStream {
    protected:
        size_t pointer = 0;
    };

    class MemoryInputStream:public MemoryStream {
    private:
        const BYTE *data;
        size_t size;

    public:
        MemoryInputStream(const void *data, size_t size) {
            this->data = (BYTE*)data;
            this->size = size;
        }

        inline void set(size_t bytes) {
            pointer = bytes;
        }

        inline size_t getBytesRead() const {
            return pointer;
        }

        __declspec(property(get = getBytesRead)) size_t BytesRead;

        inline size_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline INT32 readInt() {
            INT32 i = *(INT32*)(data+pointer);
            pointer += sizeof(INT32);
            return i;
        }
        inline UINT32 readUInt() {
            UINT32 i = *(UINT32*)(data+pointer);
            pointer += sizeof(UINT32);
            return i;
        }
        inline LONG64 readLong() {
            LONG64 i = *(LONG64*)(data+pointer);
            pointer += sizeof(LONG64);
            return i;
        }
        inline float readFloat() {
            float i = *(float*)(data+pointer);
            pointer += sizeof(float);
            return i;
        }
        inline double readDouble() {
            double i = *(double*)(data+pointer);
            pointer += sizeof(double);
            return i;
        }
        inline bool readBoolean() {
            bool i = *(bool*)(data+pointer);
            pointer += sizeof(bool);
            return i;
        }
        inline tchar *readString() {
            tchar *i = (tchar*)(data+pointer);
            pointer += (_tcslen(i)+1)*sizeof(tchar);
            return i;
        }
        inline char *readASCII() {
            char *i = (char*)(data+pointer);
            pointer += (strlen(i)+1)*sizeof(char);
            return i;
        }
        inline wchar_t *readUnicode() {
            wchar_t *i = (wchar_t*)(data+pointer);
            pointer += (wcslen(i)+1)*sizeof(wchar_t);
            return i;
        }
        inline const void *readBytes(unsigned int length) {
            void *dataToReturn = (void*)(data+pointer);
            pointer += length;
            return dataToReturn;
        }
        template<typename T>
        T &read() {
            T *dataToReturn = (T*)(data+pointer);
            pointer += sizeof(T);
            return *dataToReturn;
        }

        inline const void *getData() const {
            return (BYTE*)data;
        }

        _declspec(property(get = getData)) const void *Data;
    };

    class MemoryOutputStream:public MemoryStream {
    private:
        BYTE *data;
        size_t capacity, initial;

        inline void resize(size_t size) {
            if(capacity<pointer+size) {
                capacity += std::max(initial, size);
                BYTE *data2 = new BYTE[capacity];
                memcpy(data2, data, pointer);
                delete[] data;
                data = data2;
            }
        }

    public:
        MemoryOutputStream() {
            capacity = initial = 100;
            this->data = new BYTE[initial];
        }

        ~MemoryOutputStream() {
            delete[] data;
        }

        const void *getData() const {
            return data;
        }

        __declspec(property(get = getData)) const void *Data;

        inline size_t getBytesWritten() const {
            return pointer;
        }

        __declspec(property(get = getBytesWritten)) size_t BytesWritten;

        inline void writeInt(INT32 i) {
            resize(sizeof(INT32));
            *(INT32*)(data+pointer) = i;
            pointer += sizeof(INT32);
        }
        inline void writeUInt(UINT32 i) {
            resize(sizeof(UINT32));
            *(UINT32*)(data+pointer) = i;
            pointer += sizeof(UINT32);
        }
        inline void writeLong(LONG64 i) {
            resize(sizeof(LONG64));
            *(LONG64*)(data+pointer) = i;
            pointer += sizeof(LONG64);
        }
        inline void writeFloat(float i) {
            resize(sizeof(float));
            *(float*)(data+pointer) = i;
            pointer += sizeof(float);
        }
        inline void writeDouble(double i) {
            resize(sizeof(double));
            *(double*)(data+pointer) = i;
            pointer += sizeof(double);
        }
        inline void writeBoolean(bool i) {
            resize(sizeof(bool));
            *(bool*)(data+pointer) = i;
            pointer += sizeof(bool);
        }
        inline void writeString(const tchar *str) {
            size_t length = (_tcslen(str)+1)*sizeof(tchar);
            writeBytes(str, length);
        }
        inline void writeASCII(const char *str) {
            size_t length = (strlen(str)+1)*sizeof(char);
            writeBytes(str, length);
        }
        inline void writeUnicode(const wchar_t *str) {
            size_t length = (wcslen(str)+1)*sizeof(wchar_t);
            writeBytes(str, length);
        }
        inline void writeBytes(const void *bytes, size_t length) {
            resize(length);
            memcpy((BYTE*)data+pointer, bytes, length);
            pointer += length;
        }
        template<typename T>
        void write(const T &value) {
            size_t length = sizeof(T);
            resize(length);
            memcpy((BYTE*)data+pointer, &value, length);
            pointer += length;
        }
    };
}