#pragma once

#include "TitleBar.h"

#include "ui/layout/StackLayout.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class ToolWindow:public StackLayout {
    private:
        SharedPointer<TitleBar> titleBar;
        SharedPointer<Border> border;
        SharedPointer<ControlContainer> container;

    public:
        ToolWindow(Theme& theme) {
            titleBar = ghnew TitleBar(theme);
            border = ghnew Border();
            border->Thickness = 1;
            container = ghnew ControlContainer();
            container->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            SharedPointer<PaddingContainer> paddingContainer = ghnew PaddingContainer();
            paddingContainer->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            paddingContainer->Padding.All = 1;
            SharedPointer<VerticalLayout> verticalLayout = ghnew VerticalLayout();
            verticalLayout->Children = { titleBar, container };
            paddingContainer->Child = verticalLayout;
            Children = {
                paddingContainer,
                border
            };
        }

        inline Control* getContent() {
            return container->Child;
        }

        inline void setContent(Control* control) {
            container->Child = control;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;

        inline UnicodeString& getTitle() {
            return titleBar->Text;
        }

        inline void setTitle(const UnicodeString& text) {
            titleBar->Text = text;
        }

        __declspec(property(get = getTitle, put = setTitle)) UnicodeString& Title;
    };
}