#include "Object.h"
#include "ghcpch.h"
#include "Object.h"

#include "core/logging/Formatter.h"
#include "core/reflection/TypeBuilder.h"
#include "Exceptions.h"

#include <format>

namespace Ghurund::Core {
    const Ghurund::Core::Type& Object::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Object>(Ghurund::Core::NAMESPACE_NAME, GH_STRINGIFY(Object))
            .withModifiers(TypeModifier::ABSTRACT);

        return TYPE;
    }
    
    bool Object::equalsImpl(const Object& other) const {
        return this == &other || Type == other.Type;
    }

    Object* Object::clone() const {
        throw CloningNotSupportedException();
    }

    String Object::toString() const {
        return String(std::format(_T("{}::{}"), Type.Namespace, Type.Name).c_str());
    }
}
