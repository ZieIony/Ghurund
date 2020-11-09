#pragma once

#include "TitleBar.h"

#include "ui/layout/StackLayout.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class ToolWindow:public StackLayout {
    private:
        ScopedPointer<TitleBar> titleBar;
        ScopedPointer<Border> border;
        ScopedPointer<ControlContainer> container;

    public:
        ToolWindow(Theme& theme) {
            titleBar = ghnew TitleBar(theme);
            border = ghnew Border();
            border->Thickness = 1;
            container = ghnew ControlContainer();
            container->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            Children = {
                makePaddingContainer(
                    makeVerticalLayout({
                        titleBar,
                        container
                    }),
                    { PreferredSize::Width::FILL, PreferredSize::Height::FILL },
                    { 1,1,1,1 }
                ),
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

        inline String& getTitle() {
            return titleBar->Text;
        }

        inline void setTitle(const String& text) {
            titleBar->Text = text;
        }

        __declspec(property(get = getTitle, put = setTitle)) String& Title;
    };
}