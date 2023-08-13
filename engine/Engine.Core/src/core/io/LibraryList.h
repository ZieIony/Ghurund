#pragma once

#include "Library.h"
#include "core/collection/Map.h"

namespace Ghurund::Core {
    class LibraryList {
    private:
        List<Library*> libs;

    public:
        ~LibraryList() {
            libs.deleteItems();
        }

        void add(std::unique_ptr<Library> library) {
            libs.add(library.release());
        }

        size_t getSize() const {
            return libs.Size;
        }

        __declspec(property(get = getSize)) size_t Size;

        Library* get(const WString& name) {
            for (size_t i = 0; i < libs.Size; i++)
                if (libs[i]->Name == name)
                    return libs[i];
            return nullptr;
        }

        Library & get(size_t i) {
            return *libs[i];
        }

        void clear() {
            libs.deleteItems();
        }

        void remove(size_t i) {
            Library* lib = libs[i];
            libs.removeAt(i);
            delete lib;
        }

        size_t findFile(const FilePath& path) const {
            for (size_t i = 0; i < libs.Size;i++) {
                Library* lib = libs[i];
                if (lib->contains(path))
                    return i;
            }
            return libs.Size;
        }
    };
}