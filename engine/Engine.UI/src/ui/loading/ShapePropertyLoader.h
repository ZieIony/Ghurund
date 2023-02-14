#pragma once

#include "PropertyLoader.h"
#include "ui/loading/ShapeFactory.h"

namespace Ghurund::UI {
    class ShapePropertyLoader:public PropertyLoader {
    private:
        ShapeFactory& shapeFactory;

    public:
        ShapePropertyLoader(ShapeFactory& shapeFactory):shapeFactory(shapeFactory) {}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<Shape*>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) const override {
            auto shape = shapeFactory.makeShape(text);
            property.setRaw(&obj, &shape);
        }
    };
}