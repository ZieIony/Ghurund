#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/Drawable.h"
#include "ui/direct2d/image/SvgDocument.h"

namespace Ghurund::UI::Direct2D {
    class SvgDrawable:public Drawable {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = SvgDrawable::GET_TYPE();
#pragma endregion

    private:
        SvgDocument* drawable;

    public:
        SvgDrawable(SvgDocument* drawable) {
            this->drawable = drawable;
            drawable->addReference();
            preferredSize = { drawable->Size.Width, drawable->Size.Height };
        }

        virtual void draw(ICanvas& canvas, const FloatSize& size, const Ghurund::UI::Color& tint) const override {
            auto dst = D2D1::RectF(0, 0, size.Width, size.Height);
            canvas.drawImage(*drawable);
        }

        virtual SvgDrawable* clone() const override {
            return ghnew SvgDrawable(drawable);
        }
    };
}