#pragma once

#include "core/resource/Loader.h"
#include "core/reflection/Type.h"
#include "core/collection/Map.h"

#include <memory>

namespace Ghurund::Core {
    class LoaderCollection {
    private:
        Map<const Type*, Loader*> loaders;

    public:
        ~LoaderCollection() {
            for (auto i = loaders.begin(); i != loaders.end(); i++)
                delete i->value;
            loaders.clear();
        }

        template<typename T>
        inline void set(std::unique_ptr<Loader> loader) {
            loaders.set(&T::TYPE, loader.release());
        }

        template<typename T>
        inline Loader* get() {
            for (auto [type, loader] : loaders) {
                if (T::TYPE.isOrExtends(*type))
                    return loader;
            }
            return nullptr;
        }

        template<typename T>
        inline void remove() {
            Loader* loader = loaders.get(&T::TYPE);
            loaders.remove(&T::TYPE);
            delete loader;
        }
    };
}