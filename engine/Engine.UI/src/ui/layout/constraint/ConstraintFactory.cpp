#include "ghuipch.h"
#include "ConstraintFactory.h"

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

    Constraint* ConstraintFactory::parseParentConstraint(const AString& str, const AString* ratio, const AString* offset) const {
        float mul = ratio ? parse<float>(*ratio) : 1.0f;
        float add = offset ? parse<float>(*offset) : 0.0f;
        const AString constraintStr = str.substring(lengthOf("Parent."));
        if (constraintStr == "Left") {
            return ghnew ParentLeftConstraint(add);
        } else if (constraintStr == "Right") {
            return ghnew ParentRightConstraint(add);
        } else if (constraintStr == "Top") {
            return ghnew ParentTopConstraint(add);
        } else if (constraintStr == "Bottom") {
            return ghnew ParentBottomConstraint(add);
        } else if (constraintStr == "Width") {
            return ghnew ParentWidthConstraint(mul, add);
        } else if (constraintStr == "Height") {
            return ghnew ParentHeightConstraint(mul, add);
        } else {
            throw InvalidFormatException("Parent constraint has to be one of: 'Left', 'Right', 'Top', 'Bottom', 'Width', 'Height'");
        }
    }

    Constraint* ConstraintFactory::parseSiblingConstraint(const AString& str, const AString* ratio, const AString* offset) const {
        float mul = ratio ? parse<float>(*ratio) : 1.0f;
        float add = offset ? parse<float>(*offset) : 0.0f;
        size_t index = findEndOfNameIndex(str);
        if (str.Length < index + 2 || str.get(index + 1) != '.')
            throw InvalidFormatException(std::format("'{}' is not a valid constraint path ('.' and a constraint name expected)", str).c_str());
        const AString constraintStr = str.substring(index + 2);
        const AString siblingNameStr = str.substring(1, index - 1);
        if (constraintStr == "Left") {
            return ghnew SiblingLeftConstraint(siblingNameStr, add);
        } else if (constraintStr == "Right") {
            return ghnew SiblingRightConstraint(siblingNameStr, add);
        } else if (constraintStr == "Top") {
            return ghnew SiblingTopConstraint(siblingNameStr, add);
        } else if (constraintStr == "Bottom") {
            return ghnew SiblingBottomConstraint(siblingNameStr, add);
        } else if (constraintStr == "Width") {
            return ghnew SiblingWidthConstraint(siblingNameStr, mul, add);
        } else if (constraintStr == "Height") {
            return ghnew SiblingHeightConstraint(siblingNameStr, mul, add);
        } else {
            throw InvalidFormatException("Sibling constraint has to be one of: 'Left', 'Right', 'Top', 'Bottom', 'Width', 'Height'");
        }
    }

    Constraint* ConstraintFactory::parseValueConstraint(const AString& str) const {
        if (str == "wrap") {
            return ghnew WrapConstraint();
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

    Constraint* ConstraintFactory::parseConstraint(const AString* path, const AString* ratio, const AString* offset) const {
        if (!path && !offset)
            throw InvalidParamException("A constraint needs 'path', 'offset' or both to be defined.");
        if (path) {
            if (path->startsWith("Parent.")) {
                return parseParentConstraint(*path, ratio, offset);
            } else if (path->startsWith("'")) {
                return parseSiblingConstraint(*path, ratio, offset);
            } else if (*path == "Width") {
                float mul = ratio ? parse<float>(*ratio) : 1.0f;
                float add = offset ? parse<float>(*offset) : 0.0f;
                return ghnew SelfWidthConstraint(mul, add);
            } else if (*path == "Height") {
                float mul = ratio ? parse<float>(*ratio) : 1.0f;
                float add = offset ? parse<float>(*offset) : 0.0f;
                return ghnew SelfHeightConstraint(mul, add);
            } else {
                throw InvalidFormatException("Constraint path has to be one of: 'Parent.[constraint]', ''[sibling name]'.[constraint]', '[constraint]'");
            }
        } else {
            return parseValueConstraint(*offset);
        }
    }
    
    Constraint* ConstraintFactory::parseConstraint(const AString& str) const {
        if (str.startsWith("Parent.")) {
            return parseParentConstraint(str, nullptr, nullptr);
        } else if (str.startsWith("'")) {
            return parseSiblingConstraint(str, nullptr, nullptr);
        } else if (str == "Width") {
            return ghnew SelfWidthConstraint(1.0f, 0.0f);
        } else if (str == "Height") {
            return ghnew SelfHeightConstraint(1.0f, 0.0f);
        } else {
            return parseValueConstraint(str);
        }
    }
}