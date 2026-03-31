#pragma once

#include "DirectoryPath.h"
#include "Library.h"

#include "core/io/File.h"

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

        virtual bool contains(const WString& path) const override {
            return File(this->path / FilePath(path)).Exists;
        }

        virtual FilePath getAbsolutePath(const WString& path) const override {
            return this->path / FilePath(path);
        }

        virtual SharedPointer<Buffer> get(const WString& path) const override {
            File file(this->path / FilePath(path));
            if (!file.Exists)
                throw InvalidParamException();
            auto buffer = SharedPointer(ghnew Buffer());
            file.read(*buffer.get());
            return buffer;
        }

        virtual SharedPointer<Buffer> get(const size_t index) const override {
            File file(path.Files[index]);
            auto buffer = SharedPointer(ghnew Buffer());
            file.read(*buffer.get());
            return buffer;
        }

        virtual size_t getSize() const override {
            return path.Files.Size;
        }
    };
}