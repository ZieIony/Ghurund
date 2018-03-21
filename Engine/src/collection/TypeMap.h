#pragma once

#include "List.h"
#include "Map.h"

namespace Ghurund {
    template<class Key = size_t> class TypeMap {
    private:
        List<Object*> maps;
        unsigned int index = 0;

        template <typename Type> size_t getId() {
            static size_t id = index++;
            return id;
        }

    public:
        ~TypeMap() {
            for(size_t i = 0; i<maps.Size; i++)
                delete maps.get(i);
        }

        template<class Value> void set(const Key &key, const Value &value) {
            if(maps.Size<=getId<Value>())
                maps.add(ghnew Map<Key, Value>());
            Map<Key, Value> *map = (Map<Key, Value>*)maps.get(getId<Value>());
            map->set(key, value);
        }

        template<class Value> Value get(const Key &key) {
            if(maps.Size<=getId<Value>())
                return Value();
            Map<Key, Value> *map = (Map<Key, Value>*)maps.get(getId<Value>());
            return map->get(key);
        }

        template<class Value> void remove(const Key &key) {
            if(maps.Size<=getId<Value>())
                return;
            Map<Key, Value> *map = (Map<Key, Value>*)maps.get(getId<Value>());
            map->remove(key);
        }
    };
}