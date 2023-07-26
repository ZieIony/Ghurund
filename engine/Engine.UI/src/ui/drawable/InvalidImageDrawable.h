#pragma once

#include "Drawable.h"

namespace Ghurund::UI {
    class InvalidImageDrawable:public Drawable {
    private:
        Color backgroundColor = Color(1, 0, 0, 0.2f);
        Color borderColor = Color(1, 0, 0, 1.0f);

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        InvalidImageDrawable();

        virtual void draw(ICanvas& canvas, const Ghurund::Core::FloatSize& size, const Ghurund::UI::Color& tint) const override;

        virtual InvalidImageDrawable* clone() const override {
            return ghnew InvalidImageDrawable();
        }
    };
}