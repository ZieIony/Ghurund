#pragma once

#include "ui/layout/constraint/ParentConstraint.h"
#include "ui/layout/constraint/SiblingConstraint.h"
#include "ui/layout/constraint/SelfConstraint.h"
#include "ui/layout/constraint/WrapConstraint.h"

#include <format>

namespace Ghurund::UI {
    class ConstraintFactory {
    private:
        size_t findEndOfNameIndex(const AString& str) const;

        Constraint* parseParentConstraint(const AString& str, const AString* ratio, const AString* offset) const;

        Constraint* parseSiblingConstraint(const AString& str, const AString* ratio, const AString* offset) const;

        Constraint* parseValueConstraint(const AString& str) const;

    public:
        virtual ~ConstraintFactory() {}

        virtual Constraint* parseConstraint(const AString* path, const AString* ratio, const AString* offset) const;

        virtual Constraint* parseConstraint(const AString& str) const;
    };
}