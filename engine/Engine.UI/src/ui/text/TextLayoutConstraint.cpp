#include "ghuipch.h"
#include "TextLayoutConstraint.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& TextLayoutWidthConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextLayoutWidthConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool TextLayoutWidthConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const TextLayoutWidthConstraint& c = (const TextLayoutWidthConstraint&)other;
        return &textLayout == &c.textLayout;
    }

    const Ghurund::Core::Type& TextLayoutHeightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextLayoutHeightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool TextLayoutHeightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const TextLayoutHeightConstraint& c = (const TextLayoutHeightConstraint&)other;
        return &textLayout == &c.textLayout;
    }
}