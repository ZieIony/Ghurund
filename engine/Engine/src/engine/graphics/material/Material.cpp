#include "ghepch.h"

#include "Material.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& Material::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<Material>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}