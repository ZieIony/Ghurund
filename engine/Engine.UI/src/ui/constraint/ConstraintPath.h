#pragma once

#include "Constraint.h"
#include "core/string/String.h"
#include "ui/control/Control.h"
#include "ui/control/ControlPath.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ConstraintPath {
    private:
        ControlPath path;
        AString constraintName;

    public:
        inline static ConstraintPath parse(const AString& text) {
            size_t index = text.findLast(".");
            if (index = text.Size) {
                return ConstraintPath(ControlPath::parse(text), "");
            } else {
                return ConstraintPath(ControlPath::parse(text.substring(0, index)), text.substring(index, text.Size - index));
            }
        }

        ConstraintPath(const ControlPath& path, const AString& constraintName):path(path), constraintName(constraintName){}

        Constraint* resolve(Control& control) {
            Control* target = path.resolve(control);
            if (!target)
                return nullptr;
            return nullptr;// target->Constraints[constraintName];
        }
    };
}