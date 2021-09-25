#include "ghcpch.h"
#include "Task.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    const Ghurund::Core::Type& Task::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Task>(NAMESPACE_NAME, GH_STRINGIFY(Task))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
