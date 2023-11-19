#include "ghuipch.h"
#include "Constraint.h"
#include "OffsetConstraint.h"
#include "RatioConstraint.h"
#include "MinMaxConstraint.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Constraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Constraint>(NAMESPACE_NAME, GH_STRINGIFY(Constraint))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool Constraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const Constraint& c = (const Constraint&)other;
        return value == c.value && constant == c.constant && skipDependencies == c.skipDependencies && dependencies == c.dependencies;
    }

    const Ghurund::Core::Type& OffsetConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<OffsetConstraint>(NAMESPACE_NAME, GH_STRINGIFY(OffsetConstraint))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool OffsetConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const OffsetConstraint& c = (const OffsetConstraint&)other;
        return offset == c.offset;
    }

    const Ghurund::Core::Type& RatioConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<RatioConstraint>(NAMESPACE_NAME, GH_STRINGIFY(RatioConstraint))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool RatioConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const RatioConstraint& c = (const RatioConstraint&)other;
        return ratio == c.ratio;
    }

    const Ghurund::Core::Type& MinMaxConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<MinMaxConstraint>(NAMESPACE_NAME, GH_STRINGIFY(MinMaxConstraint))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool MinMaxConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const MinMaxConstraint& c = (const MinMaxConstraint&)other;
        return min == c.min && max == c.max;
    }
}