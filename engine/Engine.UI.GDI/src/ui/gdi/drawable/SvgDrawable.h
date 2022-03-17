#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/gdi/image/SvgDocument.h"

namespace Ghurund::UI::GDI {
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
            canvas.drawImage(*image);
        }

        virtual SvgDrawable* clone() const override {
            return ghnew SvgDrawable(image);
        }
    };
}