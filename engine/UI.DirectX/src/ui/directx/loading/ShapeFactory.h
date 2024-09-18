#pragma once

#include "ui/loading/ShapeFactory.h"
#include "ui/directx/Shape.h"

namespace Ghurund::UI::DirectX {
    class ShapeFactory:public Ghurund::UI::ShapeFactory {
    public:
        virtual std::unique_ptr<Ghurund::UI::Shape> makeShape(const AString& desc) override {
            if (desc == "rect") {
                return nullptr;
            } else if (desc.startsWith("roundRect")) {
                float radius = (float)atof(desc.substring(desc.find(",") + 1).trim().Data);
                return nullptr;
            }
            return nullptr;
        }
    };
}        
