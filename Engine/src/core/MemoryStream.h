#pragma once

#include "Ghurund.h"
#include "Logger.h"
#include <algorithm>

namespace Ghurund {
    class MemoryStream {
    protected:
        unsigned int pointer = 0;

    public:
        inline void reset() {
            pointer = 0;
        }
    };

    class MemoryInputStream:public MemoryStream {
    private:
        const BYTE *data;

    public:
        MemoryInputStream(const void *data) {
            this->data = (BYTE*)data;
        }
        inline unsigned int getBytesRead() {
            return pointer;
        }

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
    };

    class MemoryOutputStream:public MemoryStream {
    private:
        BYTE *d;
        BYTE **data;
        unsigned int capacity, initial;

        inline void resize(unsigned int size) {
            if(capacity<pointer+size) {
                capacity += std::max(initial, size);
                BYTE *data2 = new BYTE[capacity];
                memcpy(data2, *data, pointer);
                delete[] *data;
                *data = data2;
            }
        }

    public:
        MemoryOutputStream() {
            capacity = initial = 100;
            d = ghnew BYTE[initial];
            this->data = &d;
        }

        MemoryOutputStream(void **data) {
            this->data = (BYTE**)data;
            if(*this->data)
                delete[] *this->data;
            *this->data = new BYTE[100];
            capacity = initial = 100;
        }

        ~MemoryOutputStream() {
            if(d!=nullptr)
                delete[] d;
        }

        void *getData() {
            return *data;
        }

        inline unsigned int getBytesWritten() {
            return pointer;
        }

        inline void writeInt(int i) {
            resize(sizeof(int));
            *(int*)(*data+pointer) = i;
            pointer += sizeof(int);
        }
        inline void writeUInt(unsigned int i) {
            resize(sizeof(unsigned int));
            *(unsigned int*)(*data+pointer) = i;
            pointer += sizeof(unsigned int);
        }
        inline void writeLong(long i) {
            resize(sizeof(long));
            *(long*)(*data+pointer) = i;
            pointer += sizeof(long);
        }
        inline void writeFloat(float i) {
            resize(sizeof(float));
            *(float*)(*data+pointer) = i;
            pointer += sizeof(float);
        }
        inline void writeDouble(double i) {
            resize(sizeof(double));
            *(double*)(*data+pointer) = i;
            pointer += sizeof(double);
        }
        inline void writeBoolean(bool i) {
            resize(sizeof(bool));
            *(bool*)(*data+pointer) = i;
            pointer += sizeof(bool);
        }
        inline void writeChar(char i) {
            resize(sizeof(char));
            *(char*)(*data+pointer) = i;
            pointer += sizeof(char);
        }
        inline void writeUChar(unsigned char i) {
            resize(sizeof(unsigned char));
            *(unsigned char*)(*data+pointer) = i;
            pointer += sizeof(unsigned char);
        }
        inline void writeString(const tchar *str) {
            unsigned int length = (_tcslen(str)+1)*sizeof(tchar);
            resize(length);
            _tcscpy_s((tchar*)(*data+pointer), length, str);
            pointer += length;
        }
        inline void writeASCII(const char *str) {
            unsigned int length = (strlen(str)+1)*sizeof(char);
            resize(length);
            strcpy_s((char*)(*data+pointer), length, str);
            pointer += length;
        }
        inline void writeUnicode(const wchar_t *str) {
            unsigned int length = (wcslen(str)+1)*sizeof(wchar_t);
            resize(length);
            wcscpy_s((wchar_t*)(*data+pointer), length, str);
            pointer += length;
        }
        inline void writeBytes(const void *bytes, unsigned int length) {
            resize(length);
            memcpy((BYTE*)*data+pointer, bytes, length);
            pointer += length;
        }
    };
}