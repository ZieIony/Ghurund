#include "ghepch.h"

#include "Parameter.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& Parameter::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Parameter>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
