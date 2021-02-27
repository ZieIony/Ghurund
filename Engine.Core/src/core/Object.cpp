#include "Object.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    const Ghurund::Type& Object::GET_TYPE() {
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Object))
            .withModifiers(TypeModifier::ABSTRACT);

        return TYPE;
    }
}
