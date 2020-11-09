#pragma once

#include "Button.h"
#include "ImageButtonLayout.h"
#include "ui/mixin/ImageMixin.h"

namespace Ghurund::UI {
    class ImageButton:public Button, public ImageMixin {
    private:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ImageButton))
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        ImageButton(ImageButtonLayout* layout):Button(layout) {
            imageView = layout->ImageView;
        };

        ImageButton(Ghurund::UI::Theme& theme):ImageButton(ghnew ImageButtonLayout(theme)) {};

        virtual void measure(float parentWidth, float parentHeight) {
            imageView->PreferredSize = preferredSize;
            __super::measure(parentWidth, parentHeight);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}