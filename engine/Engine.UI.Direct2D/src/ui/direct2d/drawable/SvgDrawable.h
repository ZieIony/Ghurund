#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/direct2d/image/SvgDocument.h"

namespace Ghurund::UI::Direct2D {
    class SvgDrawable:public ImageDrawable {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
#pragma endregion

    private:
        SvgDocument* image;

    public:
        SvgDrawable(SvgDocument* image) {
            this->image = image;
            image->addReference();
            preferredSize = { image->Size.width, image->Size.height };
        }

        virtual void onDraw(ICanvas& canvas) override {
            auto dst = D2D1::RectF(0, 0, size.width, size.height);
            canvas.drawImage(*image);
        }

        virtual SvgDrawable* clone() const override {
            return ghnew SvgDrawable(image);
        }
    };
}