#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
    class CheckBox:public CheckBoxRadio<CheckBox> {
    protected:
        virtual void bind() override {
            __super::bind();
            if (selectable) {
                selectable->clicked += [this](Control&, const MouseClickedEventArgs&) {
                    Checked = !Checked;
                    checkedChanged();
                    return true;
                };
                selectable->stateChanged += stateHandler;
            }
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };

    class CheckBoxStyle:public CheckBoxRadioStyle {
    public:
        virtual void onStateChanged(Control& control) const;
    };
}