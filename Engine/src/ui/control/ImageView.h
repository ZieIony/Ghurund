#pragma once

#include "Control.h"
#include "ui/Drawable.h"

namespace Ghurund {
    class DrawableView: public Control {
    private:
        Drawable* drawable = nullptr;

    public:
        DrawableView(Drawable* drawable = nullptr) {
            if (drawable)
                drawable->addReference();
            this->drawable = drawable;
        }

        ~DrawableView() {
            if(drawable)
                drawable->release();
        }

        inline void setDrawable(Drawable* drawable) {
            setPointer(this->drawable, drawable);
            if (drawable)
                drawable->setSize(Size.x, Size.y);
        }

        inline Drawable* getDrawable() {
            return drawable;
        }

        __declspec(property(get = getDrawable, put = setDrawable)) Drawable* Drawable;

        virtual void layout(float x, float y, float width, float height) override {
            __super::layout(x, y, width, height);
            if (drawable)
                drawable->setSize(width, height);
        }

        virtual void draw(Canvas& canvas) override {
            if(drawable)
                drawable->draw(canvas);
        }
    };
}