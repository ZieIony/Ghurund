#pragma once

#include "ui/style/Style.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/ColorView.h"

namespace Ghurund::UI {
    class Separator:public PaddingContainer {
    private:
        ColorView* colorView;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        Separator();

        ~Separator() {
            colorView->release();
        }

        inline unsigned int getColor() const {
            return colorView->Color;
        }

        inline void setColor(unsigned int color) {
            colorView->Color = color;
        }

        __declspec(property(get = getColor, put = setColor)) unsigned int Color;

        inline float getThickness() const {
            return colorView->MinSize.width;
        }

        inline void setThickness(float thickness) {
            colorView->MinSize.width = thickness;
            colorView->MinSize.height = thickness;
        }

        __declspec(property(get = getThickness, put = setThickness)) float Thickness;

        virtual void onMeasure(float parentWidth, float parentHeight) {
            colorView->PreferredSize = preferredSize;
            __super::onMeasure(parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            __super::onLayout(x, y, width, height);
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}