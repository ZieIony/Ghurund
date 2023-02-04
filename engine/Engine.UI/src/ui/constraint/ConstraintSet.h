#pragma once

#include "Constraint.h"
#include "core/SharedPointer.h"
#include "ValueConstraint.h"

#include <utility>

namespace Ghurund::UI {
    struct ConstraintSet {
        SharedPointer<Constraint> left;
        SharedPointer<Constraint> width;
        SharedPointer<Constraint> right;
        SharedPointer<Constraint> top;
        SharedPointer<Constraint> height;
        SharedPointer<Constraint> bottom;

        ConstraintSet() {}

        ConstraintSet(const ConstraintSet& other):left(other.left), width(other.width), right(other.right), top(other.top), height(other.height), bottom(other.bottom) {}

        ConstraintSet(ConstraintSet&& other) noexcept:
            left(::std::move(other.left)), width(::std::move(other.width)), right(::std::move(other.right)),
            top(::std::move(other.top)), height(::std::move(other.height)), bottom(::std::move(other.bottom)) {}

        inline ConstraintSet& withLeft(float value) {
            this->left = ghnew ValueConstraint(value);
            return *this;
        }

        inline ConstraintSet& withLeft(Constraint* constraint) {
            this->left = constraint;
            if(constraint)
                constraint->addReference();
            return *this;
        }

        inline ConstraintSet& withWidth(float value) {
            this->width = ghnew ValueConstraint(value);
            return *this;
        }

        inline ConstraintSet& withWidth(Constraint* constraint) {
            this->width = constraint;
            if (constraint)
                constraint->addReference();
            return *this;
        }

        inline ConstraintSet& withRight(float value) {
            this->right = ghnew ValueConstraint(value);
            return *this;
        }

        inline ConstraintSet& withRight(Constraint* constraint) {
            this->right = constraint;
            if (constraint)
                constraint->addReference();
            return *this;
        }

        inline ConstraintSet& withTop(float value) {
            this->top = ghnew ValueConstraint(value);
            return *this;
        }

        inline ConstraintSet& withTop(Constraint* constraint) {
            this->top = constraint;
            if (constraint)
                constraint->addReference();
            return *this;
        }

        inline ConstraintSet& withHeight(float value) {
            this->height = ghnew ValueConstraint(value);
            return *this;
        }

        inline ConstraintSet& withHeight(Constraint* constraint) {
            this->height = constraint;
            if (constraint)
                constraint->addReference();
            return *this;
        }

        inline ConstraintSet& withBottom(float value) {
            this->bottom = ghnew ValueConstraint(value);
            return *this;
        }

        inline ConstraintSet& withBottom(Constraint* constraint) {
            this->bottom = constraint;
            if (constraint)
                constraint->addReference();
            return *this;
        }
    };
}