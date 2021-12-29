#include "ghcdxpch.h"
#include "AdapterOutput.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core::DirectX {
    const Ghurund::Core::Type& AdapterOutput::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<AdapterOutput>(Ghurund::Core::DirectX::NAMESPACE_NAME, GH_STRINGIFY(AdapterOutput))
            .withSupertype(Object::TYPE);

        return TYPE;
    }
}
