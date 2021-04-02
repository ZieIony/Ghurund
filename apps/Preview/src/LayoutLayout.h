#pragma once

#include "core/collection/PointerList.h"
#include "ui/LayoutLoader.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/ControlContainer.h"
#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"

namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class LayoutLayout:public ControlContainer {
    private:
        StackLayout* container;
        CheckBox* themeCheckBox, * enabledCheckBox;
        Button* button1, * button2, * button3, * button4;

    public:
        void init(LayoutLoader& layoutLoader) {
            PointerList<Control*> controls;
            layoutLoader.load(L"Preview/layoutLayout.xml", controls);
            Child = controls[0];

            container = (StackLayout*)rootView->find("container");
            themeCheckBox = (CheckBox*)rootView->find("themeCheckBox");
            themeCheckBox->OnCheckedChanged.add([this](CheckBox&) {
                updateTheme();
                rootView->repaint();
                return true;
            });
            enabledCheckBox = (CheckBox*)rootView->find("enabledCheckBox");
            enabledCheckBox->OnCheckedChanged.add([this](CheckBox& checkBox) {
                container->Enabled = checkBox.Checked;
                container->repaint();
                return true;
            });

            auto colorClickHandler = [this](Control& control, const MouseClickedEventArgs& args) {
                ColorView* colorView = (ColorView*)control.find(ColorView::TYPE);
                darkTheme->Colors.set(Theme::COLOR_ACCENT, colorView->Color);
                darkTheme->updateColors();
                lightTheme->Colors.set(Theme::COLOR_ACCENT, colorView->Color);
                lightTheme->updateColors();
                rootView->dispatchThemeChanged();
                return true;
            };
            button1 = (Button*)rootView->find("color1");
            button1->Clicked.add(colorClickHandler);
            button2 = (Button*)rootView->find("color2");
            button2->Clicked.add(colorClickHandler);
            button3 = (Button*)rootView->find("color3");
            button3->Clicked.add(colorClickHandler);
            button4 = (Button*)rootView->find("color4");
            button4->Clicked.add(colorClickHandler);
        }
    };
}