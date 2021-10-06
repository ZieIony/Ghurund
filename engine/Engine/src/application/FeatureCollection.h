#pragma once

#include "Feature.h"
#include "core/Concepts.h"
#include "core/SharedPointer.h"
#include "core/collection/Map.h"

namespace Ghurund {
    class FeatureCollection {
    private:
        // TODO: replace with TypeMap
        Map<Type, SharedPointer<Feature>> map;

    public:
        template<Derived<Feature> Type>
        inline void add(SharedPointer<Feature> feature) {
            map.set(Type::TYPE, feature);
        }

        template<Derived<Feature> Type>
        inline Type* get() {
            size_t index = map.indexOfKey(Type::TYPE);
            if (index == map.Size)
                return nullptr;
            return (Type*)(Feature*)map.getValue(index);
        }

        template<Derived<Feature> Type>
        inline void remove(SharedPointer<Feature> feature) {
            map.remove(Type::TYPE, feature);
        }

        SharedPointer<Feature>* begin() {
            return map.begin();
        }

        SharedPointer<Feature>* end() {
            return map.end();
        }
    };
}