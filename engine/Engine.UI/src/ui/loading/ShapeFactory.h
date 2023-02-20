#pragma once

#include "core/string/String.h"
#include "ui/Shape.h"

#include <memory>

namespace Ghurund::UI {
    __interface ShapeFactory {
        std::unique_ptr<Shape> makeShape(const AString& desc);
    };
}