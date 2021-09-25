#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
    class RadioButton:public CheckBoxRadio<RadioButton> {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual void onLayoutChanged() override;

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class RadioButtonStyle:public CheckBoxRadioStyle {
    public:
        virtual void onStateChanged(Control& control) const;
    };
}