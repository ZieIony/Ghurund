#pragma once

#include "SvgImage.h"
#include "core/reflection/TypeBuilder.h"
#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"

namespace Ghurund::UI {
    class SvgImageDrawable:public ImageDrawable {
    private:
        SvgImage* image;

    protected:
        const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(SvgImageDrawable))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        SvgImageDrawable(SvgImage* image) {
            this->image = image;
            image->addReference();
            preferredSize = { image->Size.width, image->Size.height };
        }

        virtual void onDraw(Canvas& canvas) override {
            auto dst = D2D1::RectF(0, 0, size.width, size.height);
            canvas.drawImage(*image->Data);
        }

        virtual SvgImageDrawable* clone() override {
            return ghnew SvgImageDrawable(image);
        }

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}