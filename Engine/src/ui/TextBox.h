#pragma once

#include "Control.h"

namespace Ghurund {
    class TextBox:public Control {
    private:
        UnicodeString text;

    public:
        void setText(const UnicodeString& text) {
            this->text = text;
        }

        const UnicodeString& getText()const {
            return text;
        }

        __declspec(property(get = getText, put = setText)) UnicodeString& Text;
    };
}