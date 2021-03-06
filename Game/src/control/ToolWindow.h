#pragma once

#include "TitleBar.h"
#include "ToolWindowBinding.h"

#include "ui/layout/StackLayout.h"
#include "ui/widget/ContainerWidget.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class ToolWindow:public ContainerWidget<ToolWindowBinding> {
    public:
        inline const WString& getTitle() {
            return Layout->TitleBar->Text;
        }

        inline void setTitle(const WString& text) {
            Layout->TitleBar->Text = text;
        }

        __declspec(property(get = getTitle, put = setTitle)) const WString& Title;
    };
}