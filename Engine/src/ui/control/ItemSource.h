#pragma once

#include "core/collection/List.h"

namespace Ghurund::UI {
    template<class T>
    class ItemSource {
    public:
        virtual ~ItemSource() {}

        virtual size_t getSize() const = 0;

        __declspec(property(get = getSize)) size_t Size;

        virtual T& get(size_t position) const = 0;
    };

    template<class T>
    class ListItemSource:public ItemSource<T> {
    private:
        List<T>& list;

    public:
        ListItemSource(List<T>& list):list(list) {}

        virtual size_t getSize() const override {
            return list.Size;
        }

        virtual T& get(size_t position) const override {
            return list.get(position);
        }
    };
}