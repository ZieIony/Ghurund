#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/control/ColorView.h"

namespace Ghurund::UI {
    class Separator:public ControlContainer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Separator::GET_TYPE();
#pragma endregion

    private:
        ColorView* colorView;

    protected:
        virtual void onThemeChanged() override;

        virtual void onStateChanged() override;

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
    };
}