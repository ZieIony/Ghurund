#pragma once

#include "TitleBarBinding.h"
#include "ui/control/TextBlock.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class TitleBar:public Widget<TitleBarBinding> {
    public:
        inline const WString& getText() {
            return Layout->Title->Text;
        }

        inline void setText(const WString& text) {
            Layout->Title->Text = text;
        }

        __declspec(property(get = getText, put = setText)) const WString& Text;
    };
}