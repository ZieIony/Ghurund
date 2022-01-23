#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
    class CheckBox:public CheckBoxRadio<CheckBox> {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual void bind() override {
            __super::bind();
            selectable->clicked += [this](Control&, const MouseClickedEventArgs&) {
                Checked = !Checked;
                checkedChanged();
                return true;
            };
            selectable->stateChanged += stateHandler;
        }

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