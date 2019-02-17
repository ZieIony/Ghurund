#include "FileUtils.h"

namespace Ghurund {
    Status readFile(const wchar_t * name, void *& data, size_t & size) {
        HANDLE handle = CreateFileW(name, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        DWORD derr = GetLastError();
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

    Status writeFile(const wchar_t * name, void * data, size_t size) {
        HANDLE handle = CreateFileW(name, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if(handle==INVALID_HANDLE_VALUE)
            return Status::IO;
        unsigned long bytes;
        WriteFile(handle, data, size, &bytes, false);
        if(bytes!=size)
            return Status::IO;
        CloseHandle(handle);
        return Status::OK;
    }
}