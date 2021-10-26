#pragma once

#include "core/string/String.h"
#include "ui/Shape.h"

namespace Ghurund::UI {
    __interface ShapeFactory {
        Shape* makeShape(const AString& desc);
    };
}