#pragma once

#include "ui/control/ColorView.h"

namespace Ghurund::UI {
    class BackgroundMixin {
    protected:
        ColorView* backgroundView = nullptr;

    public:
        inline void setBackgroundColor(const Color& color) {
            backgroundView->Color = color;
        }

        inline const Color& getBackgroundColor() {
            return backgroundView->Color;
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) const Color& BackgroundColor;
    };

    class BackgroundLayoutMixin {
    protected:
        ColorView* backgroundView;

    public:
        BackgroundLayoutMixin() {
            backgroundView = ghnew ColorView(0);
        }

        ~BackgroundLayoutMixin() {
            backgroundView->release();
        }

        inline ColorView* getBackgroundView() {
            return backgroundView;
        }

        __declspec(property(get = getBackgroundView)) ColorView* BackgroundView;
    };
}