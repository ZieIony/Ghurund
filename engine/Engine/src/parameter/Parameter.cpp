#include "ghpch.h"

#include "Parameter.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    const Ghurund::Core::Type& Parameter::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Parameter>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Parameter))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
