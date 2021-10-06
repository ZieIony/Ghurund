#pragma once

#include "Tree.h"
#include "Map.h"

namespace Ghurund::Core {
    template<typename Key, typename Value>
    class TreeMap:public Collection {
    private:
        template<typename Key, typename Value>
        struct MapEntry {
            Key key;
            Value value;
        };

        Tree<MapEntry<Key, Value>> items;

    public:
        TreeMap() {}

        TreeMap(const Map<Key, Value>& other):Collection(other) {
            items.addAll(other);
        }

        TreeMap(const TreeMap<Key, Value>& other):Collection(other) {
            items.addAll(other);
        }

        TreeMap(TreeMap&& other) noexcept:Collection(std::move(other)) {
            items = std::move(other.items);
            other.items = nullptr;
        }

        inline size_t getSize()const {
            return items.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void set(const Key& key, const Value& value) {
            auto entry = MapEntry(key, value);
            // TODO: add node replacing
            items.remove(entry);
            items.add(entry);
        }
        /*
        inline Value& get(const Key& key) const {
            items.
            throw std::exception("no value for given key");
        }*/

        inline void remove(const Key& key) {
            auto entry = MapEntry(key, value);
            items.remove(entry);
        }

        /*inline Value* begin() {
            return v;
        }

        inline Value* begin() const {
            return v;
        }

        inline Value* end() {
            return v + size;
        }

        inline Value* end() const {
            return v + size;
        }

        inline bool containsKey(const Key& item) const {
            for (size_t i = 0; i < size; i++)
                if (k[i] == item)
                    return true;
            return false;
        }

        inline bool containsValue(const Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return true;
            return false;
        }*/

        /*inline const Value& operator[](const Key& key) const {
            return get(key);
        }*/

        Map<Key, Value>& operator=(const Map<Key, Value>& other) {
            if (this == &other)
                return *this;
            items.clear();
            items.addAll(other);
            return *this;
        }

        Map<Key, Value>& operator=(const TreeMap<Key, Value>& other) {
            if (this == &other)
                return *this;
            items.clear();
            items.addAll(other);
            return *this;
        }

        Map<Key, Value>& operator=(const TreeMap<Key, Value>&& other) {
            if (this == &other)
                return *this;
            __super::operator=(std::move(other));
            items = std::move(other.items);
            other.items = nullptr;
            return *this;
        }
    };
}