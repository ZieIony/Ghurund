#pragma once

#include "ui/style/Theme.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/ColorView.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/button/Button.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class TitleBarLayout:public WidgetLayout {
    private:
        SharedPointer<TextBlock> title;
        SharedPointer<Button> closeButton;

    public:
        TitleBarLayout(Control* control) {
            title = (TextBlock*)control->find("title");
            closeButton = (Button*)control->find("close");
        }

        inline TextBlock* getTitle() {
            return title;
        }

        __declspec(property(get = getTitle)) TextBlock* Title;

        inline Button* getCloseButton() {
            return closeButton;
        }

        __declspec(property(get = getCloseButton)) Button* CloseButton;
    };

    class TitleBar:public Widget<TitleBarLayout> {
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