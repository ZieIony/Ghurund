#pragma once

#include "core/resource/Loader.h"
#include "core/reflection/Type.h"
#include "core/collection/Map.h"

#include <memory>

namespace Ghurund::Core {
    class LoaderCollection {
    private:
        Map<const Ghurund::Core::Type*, Loader*> loaders;

    public:
        ~LoaderCollection() {
            for (size_t i = 0; i < loaders.Size; i++)
                delete loaders.getValue(i);
        }

        inline void add(const Ghurund::Core::Type& type, std::unique_ptr<Loader> loader) {
            remove(type);
            loaders.set(&type, loader.release());
        }

        inline Loader* get(const Ghurund::Core::Type& type) {
            return loaders.get(&type);
        }

        inline void remove(const Ghurund::Core::Type& type) {
            if (loaders.containsKey(&type)) {
                Loader* loader = loaders.get(&type);
                loaders.remove(&type);
                delete loader;
            }
        }
    };
}