#pragma once

#include "core/SharedPointer.h"
#include "core/collection/Map.h"
#include "core/reflection/Type.h"
#include "core/resource/Loader.h"

#include <memory>

namespace Ghurund::Core {
    class LoaderCollection {
    private:
        Map<const Type*, SharedPointer<Loader>> loaders;

    public:
        template<typename T>
        inline void set(Loader* loader) {
            loader->addReference();
            loaders.set(&(const Ghurund::Core::Type&)T::GET_TYPE(), SharedPointer(loader));
        }

        inline Loader* get(const Type& t) const {
            for (auto [type, loader] : loaders) {
                if (t.isOrExtends(*type))
                    return loader.get();
            }
            return nullptr;
        }

        template<typename T>
        inline Loader* get() const {
            return get(T::GET_TYPE());
        }

        template<typename T>
        inline void remove() {
            loaders.remove(&T::GET_TYPE());
        }
    };
}