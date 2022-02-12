#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/direct2d/image/Bitmap.h"

namespace Ghurund::UI::Direct2D {
    class BitmapDrawable:public ImageDrawable {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

    private:
        Bitmap* image;

    public:
        BitmapDrawable(Bitmap* image);

        ~BitmapDrawable();

        virtual void onDraw(ICanvas& canvas) override;

        virtual BitmapDrawable* clone() const override {
            return ghnew BitmapDrawable(image);
        }
    };
}