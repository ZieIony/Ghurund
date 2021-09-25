#pragma once

#include "core/TypeSequence.h"
#include "List.h"

namespace Ghurund::Core {
    template<typename Owner>
    class TypeCollection {
    private:
        template<typename T>
        class CollectionSequence:public TypeSequence<Owner, size_t, T> {};

        List<void*> items;

    public:
        template<typename T>
        void add(T* t) {
            size_t id = CollectionSequence<T>::value();
            items.add(t);
        }

        template<typename T>
        T* get() {
            size_t id = CollectionSequence<T>::value();
            return items.get(id);
        }
    };
}