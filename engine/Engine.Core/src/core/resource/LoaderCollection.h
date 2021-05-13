#pragma once

#include "core/resource/Loader.h"
#include "core/reflection/Type.h"

#include <memory>

namespace Ghurund {
    class LoaderCollection {
    private:
        Map<const Ghurund::Type*, Loader*> loaders;

    public:
        ~LoaderCollection() {
            for (size_t i = 0; i < loaders.Size; i++)
                delete loaders.getValue(i);
        }

        inline void add(const Ghurund::Type& type, std::unique_ptr<Loader> loader) {
            remove(type);
            loaders.set(&type, loader.release());
        }

        inline Loader* get(const Ghurund::Type& type) {
            return loaders.get(&type);
        }

        inline void remove(const Ghurund::Type& type) {
            if (loaders.containsKey(&type)) {
                Loader* loader = loaders.get(&type);
                loaders.remove(&type);
                delete loader;
            }
        }
    };
}