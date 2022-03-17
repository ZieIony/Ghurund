#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/direct2d/image/SvgDocument.h"

namespace Ghurund::UI::Direct2D {
    class SvgDrawable:public ImageDrawable {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();
#pragma endregion

    private:
        SvgDocument* image;

    public:
        SvgDrawable(SvgDocument* image) {
            this->image = image;
            image->addReference();
            preferredSize = { image->Size.Width, image->Size.Height };
        }

        virtual void onDraw(ICanvas& canvas) override {
            auto dst = D2D1::RectF(0, 0, size.Width, size.Height);
            canvas.drawImage(*image);
        }

        virtual SvgDrawable* clone() const override {
            return ghnew SvgDrawable(image);
        }
    };
}