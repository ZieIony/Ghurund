#include "AdapterOutput.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    const Ghurund::Type& AdapterOutput::GET_TYPE() {
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(AdapterOutput))
            .withSupertype(Object::TYPE);

        return TYPE;
    }
}
