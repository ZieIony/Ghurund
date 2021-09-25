#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/image/Bitmap.h"

namespace Ghurund::UI {
    class BitmapDrawable:public ImageDrawable {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

    private:
        Bitmap* image;

    public:
        BitmapDrawable(Bitmap* image);

        ~BitmapDrawable();

        virtual void onDraw(Canvas& canvas) override;

        virtual BitmapDrawable* clone() override {
            return ghnew BitmapDrawable(image);
        }
    };
}