#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
    class RadioButton:public CheckBoxRadio {
    protected:
        static const Ghurund::Type& GET_TYPE();

        virtual void onLayoutChanged() override;

    public:
        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class RadioButtonStyle:public CheckBoxRadioStyle {
    public:
        virtual void onStateChanged(Control& control) const;
    };
}