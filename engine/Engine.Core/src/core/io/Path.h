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

        Path(Path&& path) noexcept {
            this->path = std::move(path.path);
        }

        virtual ~Path() = 0 {}

        Path& operator=(const Path& other) {
            if (this == &other)
                return *this;
            path = other.path;
            return *this;
        }

        Path& operator=(Path&& other) noexcept {
            if (this == &other)
                return *this;
            path = other.path;
            return *this;
        }

        const WString &toString() const {
            return path;
        }

        operator const WString &()const {
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