#pragma once

#include "ui/layout/constraint/ParentConstraint.h"
#include "ui/layout/constraint/SiblingConstraint.h"
#include "ui/layout/constraint/WrapConstraint.h"
#include "ui/layout/constraint/FillConstraint.h"
#include "ui/layout/constraint/RatioConstraint.h"

#include <format>

namespace Ghurund::UI {
    class ConstraintFactory {
    public:
        virtual ~ConstraintFactory() {}

        virtual Constraint* parseConstraint(const AString& str, Orientation orientation) const {
            if (str.startsWith("Parent.")) {
                const AString constraintStr = str.substring(lengthOf("Parent."));
                if (constraintStr == "Left") {
                    if (orientation == Orientation::HORIZONTAL) {
                        return ghnew ParentLeftConstraint();
                    } else {
                        throw InvalidParamException("'Left' is only valid as a horizontal constraint");
                    }
                } else if (constraintStr == "Right") {
                    return ghnew ParentRightConstraint();
                } else if (constraintStr == "Top") {
                    return ghnew ParentTopConstraint();
                } else if (constraintStr == "Bottom") {
                    return ghnew ParentBottomConstraint();
                } else if (constraintStr == "Width") {
                    return ghnew ParentWidthConstraint();
                } else if (constraintStr == "Height") {
                    return ghnew ParentHeightConstraint();
                } else {
                    throw InvalidDataException("Parent constraint has to be one of: 'Left', 'Right', 'Top', 'Bottom', 'Width', 'Height'");
                }
            } else if (str.startsWith("'")) {
                size_t index = 1;
                while (true) {
                    if (str[index] == '\\') {
                        index += 2;
                    } else {
                        index++;
                    }
                    if (index == str.Length)
                        throw InvalidDataException(std::format("'{}' is not a valid constraint path (reached EOT, closing '\'' expected)", str).c_str());
                    if (str[index] == '\'')
                        break;
                }
                if (str.Length < index + 2 || str.get(index + 1) != '.')
                    throw InvalidDataException(std::format("'{}' is not a valid constraint path ('.' and a constraint name expected)", str).c_str());
                const AString constraintStr = str.substring(index + 2);
                const AString siblingNameStr = str.substring(1, index - 1);
                if (constraintStr == "Left") {
                    return ghnew SiblingLeftConstraint(siblingNameStr);
                } else if (constraintStr == "Right") {
                    return ghnew SiblingRightConstraint(siblingNameStr);
                } else if (constraintStr == "Top") {
                    return ghnew SiblingTopConstraint(siblingNameStr);
                } else if (constraintStr == "Bottom") {
                    return ghnew SiblingBottomConstraint(siblingNameStr);
                } else if (constraintStr == "Width") {
                    return ghnew SiblingWidthConstraint(siblingNameStr);
                } else if (constraintStr == "Height") {
                    return ghnew SiblingHeightConstraint(siblingNameStr);
                } else {
                    throw InvalidDataException("Sibling constraint has to be one of: 'Left', 'Right', 'Top', 'Bottom', 'Width', 'Height'");
                }
            } else {
                if (str == "wrap") {
                    return ghnew WrapConstraint();
                } else if (str == "fill") {
                    return ghnew WidthFillConstraint();
                /*} else if (str.endsWith("%")) {
                    float value = Ghurund::Core::parse<float>(str.substring(0, str.Length - 1));
                    return ghnew WidthPercentConstraint(PreferredSize::Type::PERCENT, value);*/
                } else {
                    float value = Ghurund::Core::parse<float>(str);
                    return ghnew ValueConstraint(value);
                }
            }
            throw InvalidDataException();
        }
    };
}