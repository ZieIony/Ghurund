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
        ToolWindow() {
            titleBar = ghnew TitleBar();
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

        inline const WString& getTitle() {
            return titleBar->Text;
        }

        inline void setTitle(const WString& text) {
            titleBar->Text = text;
        }

        __declspec(property(get = getTitle, put = setTitle)) const WString& Title;
    };
}