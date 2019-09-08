#pragma once

namespace Ghurund {
    enum class TypeModifier {
        ABSTRACT
    };

    TypeModifier operator |(TypeModifier lhs, TypeModifier rhs);

    bool operator &(TypeModifier lhs, TypeModifier rhs);
}