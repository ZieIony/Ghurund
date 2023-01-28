#pragma once

#include "Constraint.h"

#include <memory>

namespace Ghurund::UI{
    struct ConstraintSet {
        std::shared_ptr<Constraint> left;
        std::shared_ptr<Constraint> width;
        std::shared_ptr<Constraint> right;
        std::shared_ptr<Constraint> top;
        std::shared_ptr<Constraint> height;
        std::shared_ptr<Constraint> bottom;
    };
}