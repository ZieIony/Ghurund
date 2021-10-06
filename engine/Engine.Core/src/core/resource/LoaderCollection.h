#pragma once

#include "core/resource/Loader.h"
#include "core/reflection/Type.h"
#include "core/collection/TypeMap.h"

#include <memory>

namespace Ghurund::Core {
    class LoaderCollection {
    private:
        TypeMap<LoaderCollection, Loader*> loaders;

    public:
        ~LoaderCollection() {
            for (auto i = loaders.begin(); i != loaders.end(); i++)
                delete* i;
            loaders.clear();
        }

        template<typename T>
        inline void set(std::unique_ptr<Loader> loader) {
            loaders.set<T>(loader.release());
        }

        template<typename T>
        inline Loader* get() {
            if (loaders.containsKey<T>())
                return loaders.get<T>();
            return nullptr;
        }

        template<typename T>
        inline void remove() {
            Loader* loader = loaders.get<T>();
            loaders.remove<T>();
            delete loader;
        }
    };
}