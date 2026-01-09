#pragma once

#include "Loader.h"

#include "core/collection/Map.h"
#include "core/object/IntrusivePointer.h"
#include "core/reflection/Type.h"

namespace Ghurund::Core {
    class LoaderCollection {
    private:
        Map<const Type*, IntrusivePointer<Loader>> loaders;

        LoaderCollection& operator=(const LoaderCollection& other) = delete;

    public:
        template<typename T>
        inline void set(Loader& loader) {
            loader.addReference();
            loaders.put(&(const Ghurund::Core::Type&)T::GET_TYPE(), IntrusivePointer(&loader));
        }

        inline Loader* get(const Type& t) const {
            for (auto& [type, loader] : loaders) {
                if (type->isOrExtends(t))
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

        inline void clear() {
            loaders.clear();
        }
    };
}