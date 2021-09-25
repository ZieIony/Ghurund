#pragma once

#include "core/string/String.h"
#include "core/io/FilePath.h"
#include <core/io/File.h>

namespace Ghurund::Core {
    class Library {
    private:
        WString name;

    public:
        Library(const WString& name):name(name) {}

        virtual ~Library() = 0 {}

        const WString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) WString& Name;

        virtual bool contains(const FilePath& path) = 0;

        virtual File* getFile(const FilePath& path) = 0;

        virtual File* getFile(const size_t index) = 0;

        virtual size_t getFileCount() const = 0;

        __declspec(property(get = getFileCount)) size_t FileCount;
    };
}