#pragma once

#include "ui/loading/ShapeFactory.h"
#include "ui/gdi/Shape.h"

namespace Ghurund::UI::GDI {
    class ShapeFactory:public Ghurund::UI::ShapeFactory {
    public:
        virtual Shape* makeShape(const AString& desc) override {
            if (desc == "rect") {
                return ghnew Rect();
            } else if (desc.startsWith("roundRect")) {
                float radius = (float)atof(desc.substring(desc.find(",") + 1).trim().Data);
                return ghnew RoundRect(radius);
            }
            return nullptr;
        }
    };
}        
