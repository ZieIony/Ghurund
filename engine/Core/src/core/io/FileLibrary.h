#pragma once

#include "Library.h"
#include "core/exception/Exceptions.h"

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

        virtual FilePath getAbsolutePath(const WString& path) const override {
            throw NotSupportedException();
        }

        virtual SharedPointer<Buffer> get(const WString& name) const override {
            return SharedPointer<Buffer>();
        }

        virtual SharedPointer<Buffer> get(const size_t index) const override {
            return SharedPointer<Buffer>();
        }

        virtual size_t getSize() const override {
            return 0;
        }
    };
}