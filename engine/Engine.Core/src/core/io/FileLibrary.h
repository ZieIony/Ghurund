#pragma once

#include "Library.h"
#include "core/Exceptions.h"

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

        virtual bool contains(const WString& path) const override {
            return false;
        }

        virtual ResourcePath getResourcePath(const WString& path) const override {
            return ResourcePath(Name, path);
        }

        virtual ResourcePath getResourcePath(const size_t index) const override {
            throw NotImplementedException();
        }

        virtual std::shared_ptr<Buffer> get(const WString& name) override {
            return nullptr;
        }

        virtual std::shared_ptr<Buffer> get(const size_t index) override {
            return nullptr;
        }

        virtual size_t getSize() const override {
            return 0;
        }
    };
}