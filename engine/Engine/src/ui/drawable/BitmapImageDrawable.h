#pragma once

#include "BitmapImage.h"
#include "core/reflection/TypeBuilder.h"
#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"

namespace Ghurund::UI {
    class BitmapImageDrawable:public ImageDrawable {
    private:
        BitmapImage* image;

    protected:
        const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(BitmapImageDrawable))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        BitmapImageDrawable(BitmapImage* image);

        ~BitmapImageDrawable();

        virtual void onDraw(Canvas& canvas) override;

        virtual BitmapImageDrawable* clone() override {
            return ghnew BitmapImageDrawable(image);
        }

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}