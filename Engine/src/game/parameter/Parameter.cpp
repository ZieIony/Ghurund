#include "Parameter.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    const Ghurund::Type& Parameter::GET_TYPE() {
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Parameter))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
