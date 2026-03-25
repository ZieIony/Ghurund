#pragma once

#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/object/SharedPointer.h"
#include "core/string/String.h"

namespace Ghurund::Core {
    struct XMLElement {
        WString name, value;
        Map<WString, WString> attributes;
        List<SharedPointer<XMLElement>> children;
    };
}
