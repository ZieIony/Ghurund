#include "ghedxpch.h"
#include "GPUResourcePointer.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& GPUResourcePointer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GPUResourcePointer>(Ghurund::Engine::DirectX::NAMESPACE_NAME, GH_STRINGIFY(GPUResourcePointer))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
