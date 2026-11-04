#include "ghepch.h"
#include "Material.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& Material::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Material>();

        static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<Material>()
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
