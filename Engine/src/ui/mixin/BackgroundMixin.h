#pragma once

#include "ui/control/ColorView.h"

namespace Ghurund::UI {
    class BackgroundMixin {
    protected:
        ColorView* backgroundView = nullptr;

    public:
        void setBackgroundColor(unsigned int color) {
            backgroundView->Color = color;
        }

        unsigned int getBackgroundColor() {
            return backgroundView->Color;
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) unsigned int BackgroundColor;
    };

    class BackgroundLayoutMixin {
    protected:
        ColorView* backgroundView;

    public:
        BackgroundLayoutMixin() {
            backgroundView = ghnew ColorView();
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