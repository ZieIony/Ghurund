#pragma once

#include "Constraint.h"
#include "ui/Orientation.h"

#include <format>

namespace Ghurund::UI {
    class ConstraintFactory {
    private:
        size_t findEndOfNameIndex(const AString& str) const;

        Constraint* parseParentConstraint(
            const AString& str,
            float ratio = 1.0f,
            float offset = 0.0f,
            float min = 0.0f,
            float max = std::numeric_limits<float>::max()
        ) const;

        Constraint* parseSiblingConstraint(
            const AString& str,
            float ratio = 1.0f,
            float offset = 0.0f,
            float min = 0.0f,
            float max = std::numeric_limits<float>::max()
        ) const;

        Constraint* parseValueConstraint(const AString& str, Orientation orientation) const;

    public:
        virtual ~ConstraintFactory() {}

        virtual Constraint* parseConstraint(
            const AString* path,
            const AString* ratio,
            const AString* offset,
            const AString* min,
            const AString* max,
            Orientation orientation
        ) const;

        virtual Constraint* parseConstraint(const AString& str, Orientation orientation) const;
    };
}