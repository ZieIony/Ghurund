#include "ghpch.h"
#include "GPUResourcePointer.h"

namespace Ghurund {
    const Ghurund::Core::Type& GPUResourcePointer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GPUResourcePointer>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(GPUResourcePointer))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
