#include "ghcpch.h"
#include "TypeMember.h"
#include "Type.h"
#include "core/Exceptions.h"
#include "core/logging/Formatter.h"

namespace Ghurund::Core {
    void TypeMember::checkParameter(size_t index, const Type& expectedType, const Type& actualType) const {
        if (expectedType != actualType)
            throw InvalidParamException(std::format("Parameter {} of type '{}' should be of type '{}'.\n", index, actualType, expectedType).c_str());
    }
}