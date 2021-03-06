#include "ghcpch.h"
#include "TypeModifier.h"

namespace Ghurund {
    TypeModifier operator |(TypeModifier lhs, TypeModifier rhs) {
        return (TypeModifier)((std::underlying_type_t<TypeModifier>)lhs | (std::underlying_type_t<TypeModifier>)rhs);
    }

    bool operator &(TypeModifier lhs, TypeModifier rhs) {
        return (std::underlying_type_t<TypeModifier>)lhs & (std::underlying_type_t<TypeModifier>)rhs;
    }
}