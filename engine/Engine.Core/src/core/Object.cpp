#include "ghcpch.h"
#include "Object.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    const Ghurund::Core::Type& Object::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Object>(Ghurund::Core::NAMESPACE_NAME, GH_STRINGIFY(Object))
            .withModifiers(TypeModifier::ABSTRACT);

        return TYPE;
    }
}
