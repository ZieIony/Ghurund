#pragma once

#include "Button.h"
#include "ImageButtonLayout.h"
#include "ui/mixin/ImageMixin.h"

namespace Ghurund::UI {
    class ImageButton:public Button, public ImageMixin {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ImageButton);

    public:
        ImageButton(ImageButtonLayout* layout):Button(layout) {
            imageView = layout->ImageView;
        };

        ImageButton(Theme& theme):ImageButton(ghnew ImageButtonLayout(theme)) {};

        virtual void measure(float parentWidth, float parentHeight) {
            imageView->PreferredSize = preferredSize;
            __super::measure(parentWidth, parentHeight);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ImageButton>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}