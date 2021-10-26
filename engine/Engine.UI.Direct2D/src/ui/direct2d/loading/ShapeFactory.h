#pragma once

#include "ui/loading/ShapeFactory.h"
#include "ui/direct2d/Shape.h"

namespace Ghurund::UI::Direct2D {
    class ShapeFactory:public Ghurund::UI::ShapeFactory {
    private:
        ID2D1Factory6& d2dFactory;

    public:
        ShapeFactory(ID2D1Factory6& d2dFactory):d2dFactory(d2dFactory) {}

        virtual Shape* makeShape(const AString& desc) override {
            if (desc == "rect") {
                return ghnew Rect(d2dFactory);
            } else if (desc.startsWith("roundRect")) {
                float radius = (float)atof(desc.substring(desc.find(",") + 1).trim().Data);
                return ghnew RoundRect(d2dFactory, radius);
            }
            return nullptr;
        }
    };
}        
