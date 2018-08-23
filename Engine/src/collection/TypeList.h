#pragma once

#include "List.h"

namespace Ghurund {
    template<class Key = size_t> class TypeList {
    private:
        List<Object*> lists;
        unsigned int index = 0;

        template <typename Type> size_t getId() {
            static size_t id = index++;
            return id;
        }

    public:
        ~TypeList() {
            for(size_t i = 0; i<lists.Size; i++)
                delete lists.get(i);
        }

        template<class Value> void add(const Value &value) {
            if(lists.Size<=getId<Value>())
                lists.add(ghnew List<Value>());
            List<Value> *list = (List<Value>*)lists.get(getId<Value>());
            list->add(value);
        }

        template<class Value> Value get(const Key &key) {
            Map<Key, Value> *map = (Map<Key, Value>*)lists.get(getId<Value>());
            return map->get(key);
        }

        template<class Value> void remove(const Key &key) {
            List<Value> *list = (List<Value>*)lists.get(getId<Value>());
            list->remove(key);
        }

        template<class Value> size_t getSize() {
            if(lists.Size<=getId<Value>())
                return 0;
            List<Value> *list = (List<Value>*)lists.get(getId<Value>());
            return list->Size;
        }
    };
}