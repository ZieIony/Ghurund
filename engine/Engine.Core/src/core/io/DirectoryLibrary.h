#pragma once

#include "DirectoryPath.h"
#include "Library.h"

namespace Ghurund::Core {
    /*
    * a file folder with resources
    */
    class DirectoryLibrary:public Library {
    private:
        DirectoryPath path;

    public:
        DirectoryLibrary(const WString& name, const DirectoryPath& path):Library(name), path(path) {}

        const DirectoryPath& getPath() const {
            return path;
        }

        __declspec(property(get = getPath)) DirectoryPath& Path;

        virtual bool contains(const FilePath& path) {
            return File(this->path / path).Exists;
        }

        virtual File* getFile(const FilePath& path) {
            return ghnew File(this->path / path);
        }

        virtual File* getFile(const size_t index) {
            return nullptr;
        }

        virtual size_t getFileCount() const {
            return 0;
        }
    };
}