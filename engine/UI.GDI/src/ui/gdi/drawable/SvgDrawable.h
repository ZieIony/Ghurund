#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/Drawable.h"
#include "ui/gdi/image/SvgDocument.h"

namespace Ghurund::UI::GDI {
    class SvgDrawable:public Drawable {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();
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
            canvas.drawImage(*drawable);
        }

        virtual SvgDrawable* clone() const override {
            return ghnew SvgDrawable(drawable);
        }
    };
}