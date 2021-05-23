#pragma once

namespace Ghurund {
    template<typename Value>
    class Queue:LinkedList {

    };

    template<typename Key, typename Value>
    class TreeMap:Tree<MapEntry<Key, Value>> {

    };

    template<typename Value>
    class TreeSet:Tree<Value> {

    };
}