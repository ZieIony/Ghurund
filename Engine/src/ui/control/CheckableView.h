#pragma once

#include "ClickableView.h"

namespace Ghurund::UI {
    class CheckableView:public ClickableView {
    private:
        bool checked = false;

    public:
        inline bool isChecked() const {
            return checked;
        }

        inline void setChecked(bool checked) {
            this->checked = checked;
            OnStateChanged();
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;
    };
}