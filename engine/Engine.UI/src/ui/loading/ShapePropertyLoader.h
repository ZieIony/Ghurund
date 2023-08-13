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
            return Ghurund::Core::getType<std::unique_ptr<Shape>&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            std::unique_ptr<Shape> shape = shapeFactory.makeShape(text);
            property.setRaw(&obj, &shape);
        }
    };
}