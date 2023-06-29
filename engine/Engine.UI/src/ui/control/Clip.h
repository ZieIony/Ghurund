#pragma once

#include "ControlContainer.h"
#include "ui/Shape.h"

namespace Ghurund::UI {
    class Clip:public ControlContainer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Clip::GET_TYPE();
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
            delete this->shape;
            if (shape) {
                this->shape = (Ghurund::UI::Shape*)shape->clone();
            } else {
                this->shape = nullptr;
            }
        }

        __declspec(property(get = getShape, put = setShape)) Ghurund::UI::Shape* Shape;

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
            if (shape)
                shape->Bounds = FloatRect{ 0, 0, width, height };
        }

        virtual void onDraw(ICanvas& canvas) override;
    };
}