#include "ghuipch.h"
#include "ConstraintFactory.h"

#include "ParentConstraint.h"
#include "SiblingConstraint.h"
#include "SelfConstraint.h"
#include "WrapConstraint.h"
#include "core/Float.h"

namespace Ghurund::UI {
    size_t ConstraintFactory::findEndOfNameIndex(const AString& str) const {
        size_t index = 1;
        while (true) {
            if (str[index] == '\\') {
                index += 2;
            } else {
                index++;
            }
            if (index == str.Length)
                throw InvalidFormatException(std::format("'{}' is not a valid constraint path (reached EOT, closing '\'' expected)", str).c_str());
            if (str[index] == '\'')
                break;
        }
        if (str.Length < index + 2 || str.get(index + 1) != '.')
            throw InvalidFormatException(std::format("'{}' is not a valid constraint path ('.' and a constraint name expected)", str).c_str());
        return index;
    }

    Constraint* ConstraintFactory::parseParentConstraint(const AString& str, float ratio, float offset, float min, float max) const {
        const AString constraintStr = str.substring(lengthOf("Parent."));
        if (constraintStr == "Left") {
            return ghnew ParentLeftConstraint(offset);
        } else if (constraintStr == "Right") {
            return ghnew ParentRightConstraint(offset);
        } else if (constraintStr == "Top") {
            return ghnew ParentTopConstraint(offset);
        } else if (constraintStr == "Bottom") {
            return ghnew ParentBottomConstraint(offset);
        } else if (constraintStr == "Width") {
            auto c = ghnew ParentWidthConstraint();
            c->Ratio = ratio;
            c->Offset = offset;
            c->Min = min;
            c->Max = max;
            return c;
        } else if (constraintStr == "Height") {
            auto c = ghnew ParentHeightConstraint();
            c->Ratio = ratio;
            c->Offset = offset;
            c->Min = min;
            c->Max = max;
            return c;
        } else {
            throw InvalidFormatException("Parent constraint has to be one of: 'Left', 'Right', 'Top', 'Bottom', 'Width', 'Height'");
        }
    }

    Constraint* ConstraintFactory::parseSiblingConstraint(const AString& str, float ratio, float offset, float min, float max) const {
        size_t index = findEndOfNameIndex(str);
        if (str.Length < index + 2 || str.get(index + 1) != '.')
            throw InvalidFormatException(std::format("'{}' is not a valid constraint path ('.' and a constraint name expected)", str).c_str());
        const AString constraintStr = str.substring(index + 2);
        const AString siblingNameStr = str.substring(1, index - 1);
        if (constraintStr == "Left") {
            auto c = ghnew SiblingLeftConstraint(siblingNameStr);
            c->Offset = offset;
            return c;
        } else if (constraintStr == "Right") {
            auto c = ghnew SiblingRightConstraint(siblingNameStr);
            c->Offset = offset;
            return c;
        } else if (constraintStr == "Top") {
            auto c = ghnew SiblingTopConstraint(siblingNameStr);
            c->Offset = offset;
            return c;
        } else if (constraintStr == "Bottom") {
            auto c = ghnew SiblingBottomConstraint(siblingNameStr);
            c->Offset = offset;
            return c;
        } else if (constraintStr == "Width") {
            auto c = ghnew SiblingWidthConstraint(siblingNameStr);
            c->Ratio = ratio;
            c->Offset = offset;
            c->Min = min;
            c->Max = max;
            return c;
        } else if (constraintStr == "Height") {
            auto c = ghnew SiblingHeightConstraint(siblingNameStr);
            c->Ratio = ratio;
            c->Offset = offset;
            c->Min = min;
            c->Max = max;
            return c;
        } else {
            throw InvalidFormatException("Sibling constraint has to be one of: 'Left', 'Right', 'Top', 'Bottom', 'Width', 'Height'");
        }
    }

    Constraint* ConstraintFactory::parseValueConstraint(const AString& str, Orientation orientation) const {
        if (str == "wrap") {
            if (orientation == Orientation::HORIZONTAL) {
                return ghnew WrapWidthConstraint();
            } else {
                return ghnew WrapHeightConstraint();
            }
            /*} else if (str.endsWith("%")) {
            float value = Ghurund::Core::parse<float>(str.substring(0, str.Length - 1));
            if (orientation == Orientation::HORIZONTAL) {
            return ghnew ParentWidthConstraint(value);
            } else {
            return ghnew ParentHeightConstraint(value);
            }*/
        } else {
            float value = Ghurund::Core::parse<float>(str);
            return ghnew ValueConstraint(value);
        }
    }

    Constraint* ConstraintFactory::parseConstraint(
        const AString* path,
        const AString* ratio,
        const AString* offset,
        const AString* min,
        const AString* max,
        Orientation orientation
    ) const {
        if (!path && !offset)
            throw InvalidParamException("A constraint needs 'path', 'offset' or both to be defined.");
        if (path) {
            float ratioValue = ratio ? parse<float>(*ratio) : 1.0f;
            if(ratioValue<=0.0f)
                throw InvalidParamException("Ratio cannot be less than or equal to 0.0f.");
            float offsetValue = offset ? parse<float>(*offset) : 0.0f;
            float minValue = min ? parse<float>(*min) : 0.0f;
            float maxValue = max ? parse<float>(*max) : std::numeric_limits<float>::max();
            if (minValue > maxValue)
                throw InvalidParamException("Min cannot be larger than max.");

            if (path->startsWith("Parent.")) {
                return parseParentConstraint(*path, ratioValue, offsetValue, minValue, maxValue);
            } else if (path->startsWith("'")) {
                return parseSiblingConstraint(*path, ratioValue, offsetValue, minValue, maxValue);
            } else if (*path == "Width") {
                auto c = ghnew SelfWidthConstraint();
                c->Ratio = ratioValue;
                c->Offset = offsetValue;
                c->Min = minValue;
                c->Max = maxValue;
                return c;
            } else if (*path == "Height") {
                auto c = ghnew SelfHeightConstraint();
                c->Ratio = ratioValue;
                c->Offset = offsetValue;
                c->Min = minValue;
                c->Max = maxValue;
                return c;
            } else {
                throw InvalidFormatException("Constraint path has to be one of: 'Parent.[constraint]', ''[sibling name]'.[constraint]', '[constraint]'");
            }
        } else {
            return parseValueConstraint(*offset, orientation);
        }
    }
    
    Constraint* ConstraintFactory::parseConstraint(const AString& str, Orientation orientation) const {
        if (str.startsWith("Parent.")) {
            return parseParentConstraint(str);
        } else if (str.startsWith("'")) {
            return parseSiblingConstraint(str);
        } else if (str == "Width") {
            return ghnew SelfWidthConstraint();
        } else if (str == "Height") {
            return ghnew SelfHeightConstraint();
        } else {
            return parseValueConstraint(str, orientation);
        }
    }
}