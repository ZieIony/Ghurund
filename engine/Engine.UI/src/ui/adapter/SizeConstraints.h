#pragma once

#include <ui/constraint/Constraint.h>

namespace Ghurund::UI {
    class SizeConstraints {
    public:
        SharedPointer<Constraint> width, height;

        SizeConstraints() {}

        SizeConstraints(const SharedPointer<Constraint>& width, const SharedPointer<Constraint>& height)
            :width(width), height(height) {}
    };
}