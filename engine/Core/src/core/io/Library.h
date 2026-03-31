#pragma once

#include "FilePath.h"

#include "core/Buffer.h"
#include "core/object/SharedPointer.h"
#include "core/string/String.h"

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

        virtual bool contains(const WString& path) const = 0;

        virtual FilePath getAbsolutePath(const WString& path) const = 0;

        virtual SharedPointer<Buffer> get(const WString& path) const = 0;

        virtual SharedPointer<Buffer> get(const size_t index) const = 0;

        virtual size_t getSize() const = 0;

        __declspec(property(get = getSize)) size_t Size;
    };
}