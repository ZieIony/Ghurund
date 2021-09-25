#pragma once

#include "Library.h"

namespace Ghurund::Core {
    /*
    * stored in a file
    */
    class FileLibrary:public Library {
    private:
        FilePath path;

    public:
        FileLibrary(const WString& name, const FilePath& path):Library(name), path(path) {}

        const FilePath& getPath() const {
            return path;
        }

        __declspec(property(get = getPath)) FilePath& Path;

        virtual bool contains(const FilePath& path) {
            return false;
        }

        virtual File* getFile(const FilePath& name) override {
            return nullptr;
        }

        virtual File* getFile(const size_t index) override {
            return nullptr;
        }

        virtual size_t getFileCount() const override {
            return 0;
        }
    };
}