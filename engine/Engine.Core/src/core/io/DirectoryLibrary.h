#pragma once

#include "DirectoryPath.h"
#include "Library.h"
#include "core/resource/ResourcePath.h"

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

        virtual ResourcePath getResourcePath(const WString& path) const override {
            return ResourcePath(this->path / FilePath(path));
        }

        virtual ResourcePath getResourcePath(const size_t index) const override {
            return ResourcePath(path.Files[index]);
        }

        virtual std::shared_ptr<Buffer> get(const WString& path) override {
            File file(this->path / FilePath(path));
            auto buffer = std::make_shared<Buffer>();
            file.read(*buffer.get());
            return buffer;
        }

        virtual std::shared_ptr<Buffer> get(const size_t index) override {
            File file(path.Files[index]);
            auto buffer = std::make_shared<Buffer>();
            file.read(*buffer.get());
            return buffer;
        }

        virtual size_t getSize() const override {
            return path.Files.Size;
        }
    };
}