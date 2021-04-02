#pragma once

#include "core/collection/Map.h"
#include "core/string/String.h"
#include "core/io/FilePath.h"

namespace Ghurund {
    class Library {
    private:
        WString name;
        DirectoryPath path;

    public:
        Library(const WString& name, const DirectoryPath& path):name(name), path(path) {}

        const WString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) WString& Name;

        const DirectoryPath& getPath() const {
            return path;
        }

        __declspec(property(get = getPath)) DirectoryPath& Path;
    };

    class LibraryList {
    private:
        List<Library*> libs;

    public:
        ~LibraryList() {
            libs.deleteItems();
        }

        void add(const WString& name, const DirectoryPath& path) {
            libs.add(ghnew Library(name, path.AbsolutePath));
        }

        size_t getSize() const {
            return libs.Size;
        }

        __declspec(property(get = getSize)) size_t Size;

        const Library* get(const WString& name) const {
            for (size_t i = 0; i < libs.Size; i++)
                if (libs[i]->Name == name)
                    return libs[i];
            return nullptr;
        }

        const Library & get(size_t i) const {
            return *libs[i];
        }

        void clear() {
            libs.deleteItems();
        }

        void remove(size_t i) {
            libs.removeAt(i);
        }

        size_t findFile(const FilePath & path) const {
            for (size_t i = 0; i < libs.Size; i++) {
                if (path.toString().startsWith(libs[i]->Path.toString().Data))
                    return i;
            }
            return libs.Size;
        }
    };
}