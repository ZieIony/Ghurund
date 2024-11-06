#include "ghepch.h"

#include "IMaterial.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& IMaterial::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<IMaterial>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}