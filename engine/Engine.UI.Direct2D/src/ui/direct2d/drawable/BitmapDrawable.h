#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/Drawable.h"
#include "ui/direct2d/image/Bitmap.h"

namespace Ghurund::UI::Direct2D {
    class BitmapDrawable:public Drawable {
    private:
        Bitmap* image;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        BitmapDrawable(Bitmap* image);

        ~BitmapDrawable();

        virtual void draw(ICanvas& canvas, const FloatSize& size, const Ghurund::UI::Color& tint) const override;

        virtual BitmapDrawable* clone() const override {
            return ghnew BitmapDrawable(image);
        }
    };
}