#pragma once

#include "ui/layout/constraint/Side.h"
#include "core/Exceptions.h"
#include "core/string/String.h"
#include "ui/layout/constraint/Constraint.h"
#include "core/SharedPointer.h"
#include "core/DataParsing.h"
#include "ui/control/ControlPath.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ConstraintLayout;

    class Guide {
    public:
        enum class Type {
            PIXELS, PERCENT
        };

        AString name;
        ControlPath constraintPath;
        float value = 0.0f;
        Type type;
        Side side;
        Constraint* positionConstraint;
        Constraint* sizeConstraint;

        void resolve(ConstraintLayout& parent);

        float getValue() {
            if (type == Type::PIXELS) {
                return (positionConstraint ? positionConstraint->Value : 0.0f) + value;
            } else {
                return (positionConstraint ? positionConstraint->Value : 0.0f) + sizeConstraint->Value * value;
            }
        }

        __declspec(property(get = getValue)) float Value;

        static Guide load(const tinyxml2::XMLElement& xml);
    };

    class GuideConstraint:public Constraint {
    private:
        Guide& guide;

    public:
        GuideConstraint(Guide& guide):guide(guide) {}

        virtual void evaluate() override {
            value = guide.Value;
        }
    };

}
