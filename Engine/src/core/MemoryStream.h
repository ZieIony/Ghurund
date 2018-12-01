#pragma once

#include "Ghurund.h"
#include "Logger.h"
#include <algorithm>

namespace Ghurund {
    class MemoryStream {
    protected:
        unsigned long pointer = 0;
    };

    class MemoryInputStream:public MemoryStream {
    private:
        const BYTE *data;
        unsigned long size;

    public:
        MemoryInputStream(const void *data, unsigned long size) {
            this->data = (BYTE*)data;
            this->size = size;
        }

        inline void set(unsigned long bytes) {
            pointer = bytes;
        }

        inline unsigned long getBytesRead() const {
            return pointer;
        }

        __declspec(property(get = getBytesRead)) unsigned long BytesRead;

        inline unsigned long getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) unsigned long Size;

        inline int readInt() {
            int i = *(int*)(data+pointer);
            pointer += sizeof(int);
            return i;
        }
        inline unsigned int readUInt() {
            unsigned int i = *(unsigned int*)(data+pointer);
            pointer += sizeof(unsigned int);
            return i;
        }
        inline long readLong() {
            long i = *(long*)(data+pointer);
            pointer += sizeof(long);
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
        inline char readChar() {
            char i = *(char*)(data+pointer);
            pointer += sizeof(char);
            return i;
        }
        inline unsigned char readUChar() {
            char i = *(unsigned char*)(data+pointer);
            pointer += sizeof(unsigned char);
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
        inline void *readBytes(unsigned int length) {
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
        unsigned long capacity, initial;

        inline void resize(unsigned long size) {
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

        inline unsigned long getBytesWritten() const {
            return pointer;
        }

        __declspec(property(get = getBytesWritten)) unsigned long BytesWritten;

        inline void writeInt(int i) {
            resize(sizeof(int));
            *(int*)(data+pointer) = i;
            pointer += sizeof(int);
        }
        inline void writeUInt(unsigned int i) {
            resize(sizeof(unsigned int));
            *(unsigned int*)(data+pointer) = i;
            pointer += sizeof(unsigned int);
        }
        inline void writeLong(long i) {
            resize(sizeof(long));
            *(long*)(data+pointer) = i;
            pointer += sizeof(long);
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
        inline void writeChar(char i) {
            resize(sizeof(char));
            *(char*)(data+pointer) = i;
            pointer += sizeof(char);
        }
        inline void writeUChar(unsigned char i) {
            resize(sizeof(unsigned char));
            *(unsigned char*)(data+pointer) = i;
            pointer += sizeof(unsigned char);
        }
        inline void writeString(const tchar *str) {
            unsigned int length = (_tcslen(str)+1)*sizeof(tchar);
            writeBytes(str, length);
        }
        inline void writeASCII(const char *str) {
            unsigned int length = (strlen(str)+1)*sizeof(char);
            writeBytes(str, length);
        }
        inline void writeUnicode(const wchar_t *str) {
            unsigned int length = (wcslen(str)+1)*sizeof(wchar_t);
            writeBytes(str, length);
        }
        inline void writeBytes(const void *bytes, unsigned int length) {
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