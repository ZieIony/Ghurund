#pragma once

#include "core/string/String.h"
#include "Constraint.h"

#include <tinyxml2.h>

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

        static Chain* load(const tinyxml2::XMLElement& xml) {
            return nullptr;
        }
    };
}
