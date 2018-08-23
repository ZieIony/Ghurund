#pragma once

#include "Ghurund.h"
#include "collection/String.h"

namespace Ghurund {
    class File {
    private:
        tchar *name = nullptr;
        size_t size = 0;
        void *data = nullptr;

    public:

        File(const tchar *name) {
            safeCopyStr(&this->name, name);
        }

        File(const String &name) {
            const tchar *text = name.getData();
            safeCopyStr(&this->name, text);
        }

        ~File() {
            delete[] name;
            delete[] data;
        }

        const size_t getSize() const { return size; }

        __declspec(property(get = getSize)) size_t Size;

        const tchar *getName() const { return name; }

        void setName(const tchar *val) {
            safeCopyStr(&name, val);
        }

        __declspec(property(get = getName, put = setName)) tchar *Name;

        const void *getData()const {
            return data;
        }

        __declspec(property(get = getData)) const void *Data;

        void setData(const void *data, size_t size) {
            if(this->data!=nullptr)
                delete[] this->data;
            this->size = size;
            this->data = ghnew BYTE[size];
            memcpy(this->data, data, size);
        }

        Status read() {
            HANDLE handle = CreateFile(name, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if(handle==INVALID_HANDLE_VALUE)
                return Status::IO;
            if(data!=nullptr)
                delete[] data;
            unsigned long bytes;
            size = GetFileSize(handle, nullptr);
            data = ghnew BYTE[size];
            ReadFile(handle, data, size, &bytes, false);
            CloseHandle(handle);
            if(bytes!=size)
                return Status::IO;
            return Status::OK;
        }

        Status write() {
            HANDLE handle = CreateFile(name, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if(handle==INVALID_HANDLE_VALUE)
                return Status::IO;
            unsigned long bytes;
            WriteFile(handle, data, size, &bytes, false);
            if(bytes!=size)
                return Status::IO;
            CloseHandle(handle);
            return Status::OK;
        }

        bool exists() const {
            DWORD attributes = GetFileAttributes(name);

            return (attributes != INVALID_FILE_ATTRIBUTES &&
                    !(attributes & FILE_ATTRIBUTE_DIRECTORY));
        }

        __declspec(property(get = exists)) bool Exists;
    };
}