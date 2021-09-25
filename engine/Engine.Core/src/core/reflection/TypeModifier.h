#pragma once

namespace Ghurund::Core {
    enum class TypeModifier {
        ABSTRACT = 1, TEMPLATE = 2
    };

    TypeModifier operator |(TypeModifier lhs, TypeModifier rhs);

    bool operator &(TypeModifier lhs, TypeModifier rhs);
}