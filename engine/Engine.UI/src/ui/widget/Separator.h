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

        inline void setColor(const ColorAttr& color) {
            colorView->Color = color;
        }

        __declspec(property(put = setColor)) const ColorAttr& Color;

        inline float getThickness() const {
            return colorView->Size.Width;
        }

        inline void setThickness(float thickness) {
            //colorView->MinSize = { thickness, thickness };
        }

        __declspec(property(get = getThickness, put = setThickness)) float Thickness;

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}