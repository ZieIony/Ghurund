#pragma once

#include "core/string/String.h"
#include "core/io/FilePath.h"
#include <core/io/File.h>

#include <memory>

namespace Ghurund::Core {
    class ResourcePath;

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

        virtual bool contains(const WString& path) const = 0;

        virtual ResourcePath getResourcePath(const WString& path) const = 0;

        virtual ResourcePath getResourcePath(const size_t index) const = 0;

        virtual std::shared_ptr<Buffer> get(const WString& path) = 0;

        virtual std::shared_ptr<Buffer> get(const size_t index) = 0;

        virtual size_t getSize() const = 0;

        __declspec(property(get = getSize)) size_t Size;
    };
}