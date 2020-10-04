#pragma once

#include "ui/widget/Layout.h"
#include "ui/control/ColorView.h"
#include "ui/control/StackLayout.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/ImageView.h"
#include "ui/control/LinearLayout.h"
#include "ui/control/Border.h"

namespace Ghurund::UI {
    class DropDown;
    class Theme;

    class DropDownLayout:public Layout {
    private:
        Theme& theme;
        Border* border;
        HorizontalLayout* row;
        ImageView* imageView;
        PaddingContainer* iconPadding;
        StackLayout* stack;
        ColorView* backgroundView;
        ControlContainer* container;

    public:
        DropDownLayout(Theme& theme):theme(theme) {
            border = ghnew Border();
            row = ghnew HorizontalLayout();
            imageView = ghnew ImageView();
            iconPadding = ghnew PaddingContainer();
            stack = ghnew StackLayout();
            backgroundView = ghnew ColorView();
            container = ghnew ControlContainer();
            iconPadding->Child = imageView;
            iconPadding->Padding.All = 4;
            row->Children = { container, iconPadding };
            stack->Children = { backgroundView, row, border };
            root = stack;
        }

        ~DropDownLayout() {
            border->release();
            iconPadding->release();
            stack->release();
            backgroundView->release();
        }

        inline Control* getContent() {
            return container->Child;
        }

        inline void setContent(Control* control) {
            container->Child = control;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;

        void onStateChanged(DropDown& dropDown) {}
    };

}