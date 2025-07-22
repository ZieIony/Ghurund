#pragma once

#include "core/IntrusivePointer.h"
#include "core/collection/Map.h"
#include "core/reflection/Type.h"
#include "core/resource/Loader.h"

namespace Ghurund::Core {
    class LoaderCollection {
    private:
        Map<const Type*, IntrusivePointer<Loader>> loaders;

    public:
        template<typename T>
        inline void set(NotNull<Loader> loader) {
            loader->addReference();
            loaders.put(&(const Ghurund::Core::Type&)T::GET_TYPE(), IntrusivePointer(&loader));
        }

        inline Loader* get(const Type& t) const {
            for (auto& [type, loader] : loaders) {
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

        inline void clear() {
            loaders.clear();
        }
    };
}