#pragma once

#include <ui/constraint/Constraint.h>

namespace Ghurund::UI {
    class SizeConstraints {
    public:
        IntrusivePointer<Constraint> width, height;

        SizeConstraints() {}

        SizeConstraints(const IntrusivePointer<Constraint>& width, const IntrusivePointer<Constraint>& height)
            :width(width), height(height) {}
    };
}