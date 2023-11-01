#pragma once

#include "PropertyLoader.h"
#include "core/reflection/Type.h"
#include "core/collection/Map.h"

#include <memory>

namespace Ghurund::UI {
    class PropertyLoaderCollection {
    private:
        Map<const Type*, PropertyLoader*> loaders;

    public:
        ~PropertyLoaderCollection() {
            for (auto i = loaders.begin(); i != loaders.end(); i++)
                delete i->value;
            loaders.clear();
        }

        inline void add(std::unique_ptr<PropertyLoader> loader) {
            PropertyLoader* propertyLoader = loader.release();
            loaders.put(&propertyLoader->getType(), propertyLoader);
        }

        inline PropertyLoader* get(const Type& t) {
            for (auto [type, loader] : loaders) {
                if (type->isOrExtends(t))
                    return loader;
            }
            return nullptr;
        }

        template<typename T>
        inline void remove() {
            PropertyLoader* loader = loaders.get(&getType<T>());
            loaders.remove(&getType<T>());
            delete loader;
        }
    };
}