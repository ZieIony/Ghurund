#include "ghpch.h"
#include "AdapterOutput.h"

namespace Ghurund {
    const Ghurund::Core::Type& AdapterOutput::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<AdapterOutput>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(AdapterOutput))
            .withSupertype(Object::TYPE);

        return TYPE;
    }
}
