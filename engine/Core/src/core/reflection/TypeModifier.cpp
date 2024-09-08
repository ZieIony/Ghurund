#include "ghcpch.h"
#include "TypeModifier.h"

namespace Ghurund::Core {
    TypeModifier operator |(TypeModifier lhs, TypeModifier rhs) {
        return (TypeModifier)((std::underlying_type_t<TypeModifier>)lhs | (std::underlying_type_t<TypeModifier>)rhs);
    }

    TypeModifier& operator |=(TypeModifier& lhs, TypeModifier rhs) {
        return lhs = (TypeModifier)((std::underlying_type_t<TypeModifier>)lhs | (std::underlying_type_t<TypeModifier>)rhs);
    }

    bool operator &(TypeModifier lhs, TypeModifier rhs) {
        return (std::underlying_type_t<TypeModifier>)lhs & (std::underlying_type_t<TypeModifier>)rhs;
    }
}