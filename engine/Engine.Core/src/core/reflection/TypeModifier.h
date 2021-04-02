#pragma once

namespace Ghurund {
    enum class TypeModifier {
        ABSTRACT = 1, TEMPLATE = 2
    };

    TypeModifier operator |(TypeModifier lhs, TypeModifier rhs);

    bool operator &(TypeModifier lhs, TypeModifier rhs);
}