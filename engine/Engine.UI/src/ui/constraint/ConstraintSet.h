#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"

namespace Ghurund::UI {
    class ConstraintInitializer {
    private:
        SharedPointer<Constraint> constraint;

        ConstraintInitializer(const ConstraintInitializer& other) = delete;

        ConstraintInitializer(ConstraintInitializer& other) = delete;

    public:
        ConstraintInitializer():constraint(nullptr) {}

        ConstraintInitializer(float value):constraint(ghnew ValueConstraint(value)) {}

        template<class ConstraintType>
        ConstraintInitializer(SharedPointer<ConstraintType> constraint) {
            if (constraint != nullptr) {
                constraint->addReference();
                this->constraint.set(constraint.get());
            }
        }

        ConstraintInitializer(ConstraintInitializer&& other):constraint(std::move(other.constraint)) {}

        SharedPointer<Constraint> get() const {
            return constraint;
        }

        bool operator ==(nullptr_t) const {
            return constraint == nullptr;
        }
    };

    struct ConstraintSet {
        ConstraintInitializer left,width,right,top,height,bottom;
    };
}