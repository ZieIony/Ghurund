#include "ghuipch.h"
#include "Guide.h"

#include "ConstraintLayout.h"
#include "core/math/Float.h"

namespace Ghurund::UI {
    void Guide::resolve(ConstraintLayout& parent) {
        /*if (constraintPath.startsWith("parent.")) {
            auto sideAttr = constraintPath.substring(strlen("parent."));
            if (sideAttr == "left") {
                side = Side::LEFT;
            } else if (sideAttr == "top") {
                side = Side::TOP;
            } else if (sideAttr == "right") {
                side = Side::RIGHT;
                positionConstraint = &parent.Width;
            } else if (sideAttr == "bottom") {
                side = Side::BOTTOM;
                positionConstraint = &parent.Height;
            } else if (sideAttr == "width") {
                side = Side::RIGHT;
                sizeConstraint = &parent.Width;
            } else if (sideAttr == "height") {
                side = Side::BOTTOM;
                sizeConstraint = &parent.Height;
            } else {
                throw InvalidDataException("Side has to be one of the following: 'left', 'top', 'right', 'bottom'.");
            }
        } else {
            size_t index = constraintPath.find(".");
            if (index != constraintPath.Size) {
                auto constraintOwner = constraintPath.substring(0, index);
                auto sideAttr = constraintPath.substring(constraintOwner.Size);
                for (Control* control : parent.Children) {
                    if (control->Name && *control->Name == constraintOwner) {
                        if (sideAttr == "left") {
                            side = Side::LEFT;
                            positionConstraint = &control->Left;
                        } else if (sideAttr == "top") {
                            side = Side::TOP;
                            positionConstraint = &control->Top;
                        } else if (sideAttr == "right") {
                            side = Side::RIGHT;
                            positionConstraint = &control->Right;
                        } else if (sideAttr == "bottom") {
                            side = Side::BOTTOM;
                            positionConstraint = &control->Bottom;
                        } else if (sideAttr == "width") {
                            side = Side::RIGHT;
                            positionConstraint = &control->Left;
                            sizeConstraint = &control->Width;
                        } else if (sideAttr == "height") {
                            side = Side::BOTTOM;
                            positionConstraint = &control->Top;
                            sizeConstraint = &control->Height;
                        } else {
                            throw InvalidDataException("Side has to be one of the following: 'left', 'top', 'right', 'bottom'.");
                        }
                        return;
                    }
                }
                throw InvalidDataException(std::format("Could not find control '{}'.", constraintOwner).c_str());
            } else if (constraintPath == name) {
                throw InvalidDataException("Guides cannot reference themselves.");
            } else {
                for (Guide& guide : parent.Guides) {
                    if (&guide == this)
                        continue;
                    if (guide.name == constraintPath) {
                        side = guide.side;
                        positionConstraint = ghnew GuideConstraint(guide);
                        return;
                    }
                }
                throw InvalidDataException(std::format("Could not find guide '{}'.", constraintPath).c_str());
            }
        }*/
    }

    Guide Guide::load(const XMLElement& xml) {
        auto nameAttr = xml.findAttribute(L"name");
        if (!nameAttr)
            throw InvalidDataException("Attribute 'name' is required for a Guide.");
        AString name = convertText<wchar_t, char>(*nameAttr);
        auto constraintAttr = xml.findAttribute(L"constraint");
        if (!constraintAttr)
            throw InvalidDataException("Attribute 'constraint' is required for a Guide.");
        ControlPath constraint = parse<ControlPath>(convertText<wchar_t, char>(*constraintAttr));
        auto valueAttr = xml.findAttribute(L"value");
        float value = 0.0f;
        Type type = Type::PIXELS;
        if (valueAttr) {
            AString valueStr = convertText<wchar_t, char>(*valueAttr);
            if (valueStr.endsWith("%")) {
                value = parse<float>(valueStr.substring(0, valueStr.Length - 1));
                type = Type::PERCENT;
            } else {
                value = parse<float>(convertText<wchar_t, char>(*valueAttr));
            }
        }

        return { name, constraint, value, type };
    }

}
