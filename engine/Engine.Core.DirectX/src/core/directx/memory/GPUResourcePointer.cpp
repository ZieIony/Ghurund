#include "ghcdxpch.h"
#include "GPUResourcePointer.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core::DirectX {
    const Ghurund::Core::Type& GPUResourcePointer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GPUResourcePointer>(Ghurund::Core::DirectX::NAMESPACE_NAME, GH_STRINGIFY(GPUResourcePointer))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
