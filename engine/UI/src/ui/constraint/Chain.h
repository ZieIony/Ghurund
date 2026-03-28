#pragma once

#include "Constraint.h"

#include "core/string/String.h"
#include <core/xml/XMLElement.h>

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Chain {
    public:
        enum class Type {
            PIXELS, PERCENT
        };

        AString name;
        AString constraintPath;
        float value = 0.0f;
        Type type;
        Constraint* start,* end;

        static Chain* load(const XMLElement& xml) {
            return nullptr;
        }
    };
}
