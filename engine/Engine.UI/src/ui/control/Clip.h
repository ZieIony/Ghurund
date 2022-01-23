#pragma once

#include "ControlContainer.h"
#include "ui/Shape.h"

namespace Ghurund::UI {
    class Clip:public ControlContainer {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        Shape* shape = nullptr;

    public:
        ~Clip() {
            delete shape;
        }

        inline Shape* getShape() {
            return shape;
        }

        inline void setShape(Shape* shape) {
            this->shape = shape;
        }

        __declspec(property(get = getShape, put = setShape)) Ghurund::UI::Shape* Shape;

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
            if (shape)
                shape->Bounds = FloatRect{ 0, 0, width, height };
        }

        virtual void onDraw(ICanvas& canvas) override;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;
    };
}