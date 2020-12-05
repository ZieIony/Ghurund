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
        ImageButton(ImageButtonLayout* layout = ghnew ImageButtonLayout()):Button(layout) {
            imageView = layout->ImageView;
        };

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}