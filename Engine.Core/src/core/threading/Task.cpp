#include "ghcpch.h"
#include "Task.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    const Ghurund::Type& Task::GET_TYPE() {
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Task))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
