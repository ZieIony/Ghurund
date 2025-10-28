#pragma once

#include "core/string/String.h"
#include "ui/Shape.h"

#include <memory>

namespace Ghurund::UI {
    class ShapeFactory:Noncopyable {
    public:
        virtual std::unique_ptr<UI::Shape> makeShape(const AString& desc) = 0;
    };
}