#pragma once

#include "Common.h"
#include "core/io/FileUtils.h"
#include "FilePath.h"
#include "core/string/String.h"

namespace Ghurund::Core {
    class File {
    private:
        FilePath path;
        size_t size = 0;
        void* data = nullptr;

    public:
        File(const FilePath& path):path(path.AbsolutePath) {}

        ~File() {
            delete[] data;
        }

        const size_t getSize() const { return size; }

        __declspec(property(get = getSize)) size_t Size;

        const FilePath& getPath() const { return path; }

        void setPath(const FilePath& val) {
            this->path = val.AbsolutePath;
        }

        __declspec(property(get = getPath, put = setPath)) FilePath& Path;

        const void* getData()const {
            return data;
        }

        __declspec(property(get = getData)) const void* Data;

        void setData(const void* data, size_t size) {
            if (this->data != nullptr)
                delete[] this->data;
            this->size = size;
            this->data = ghnew uint8_t[size];
            memcpy(this->data, data, size);
        }

        Status read() {
            return readFile(path.toString().Data, data, size);
        }

        Status write() {
            return writeFile(path.toString().Data, data, size);
        }

        bool exists() const;

        __declspec(property(get = exists)) bool Exists;
    };
}