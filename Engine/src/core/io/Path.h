#pragma once

#include "core/string/String.h"

namespace Ghurund {

    class Path {
    protected:
        WString path;

    public:
        Path(const WString &path):path(path) {
            this->path.replace(L'/', L'\\');
        }

        virtual ~Path() = 0 {}

        const WString &get() const {
            return path;
        }

        operator const WString &()const {
            return path;
        }

        operator const wchar_t *()const {
            return path;
        }

        size_t getLength() const {
            return path.Length;
        }

        __declspec(property(get = getLength)) size_t Length;

        bool operator==(const Path &otherPath) const {
            return path==otherPath.path;
        }

        bool operator==(const Path &otherPath) {
            return path==otherPath.path;
        }
    };
}