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

    template<class T, class ListType = List<T>>
    class ListItemSource:public ItemSource<T> {
    private:
        ListType items;

    public:
        virtual size_t getSize() const override {
            return items.Size;
        }

        virtual T& get(size_t position) const override {
            return items.get(position);
        }

        inline ListType& getItems() {
            return items;
        }

        __declspec(property(get = getItems)) ListType& Items;
    };
}