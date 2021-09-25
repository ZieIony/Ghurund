#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
    class CheckBox:public CheckBoxRadio<CheckBox> {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual void onLayoutChanged() override;

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class CheckBoxStyle:public CheckBoxRadioStyle {
    public:
        virtual void onStateChanged(Control& control) const;
    };
}