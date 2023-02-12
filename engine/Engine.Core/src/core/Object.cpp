#include "ghcpch.h"
#include "Object.h"

#include "core/logging/Formatter.h"
#include "core/reflection/TypeBuilder.h"

#include <format>

namespace Ghurund::Core {
    const Ghurund::Core::Type& Object::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Object>(Ghurund::Core::NAMESPACE_NAME, GH_STRINGIFY(Object))
            .withModifiers(TypeModifier::ABSTRACT);

        return TYPE;
    }
    
    String Object::toString() const {
        return String(std::format(_T("{}::{}"), Type.Namespace, Type.Name).c_str());
    }
}
