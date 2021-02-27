#pragma once

#include "core/Event.h"
#include "ui/widget/Widget.h"
#include "LayoutBinding.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include <ui/widget/tab/TabContainer.h>

namespace Demo {
    using namespace Ghurund::UI;

    enum class ThemeType {
        LIGHT, DARK
    };

    class DemoLayout:public Widget<LayoutBinding> {
    protected:
        virtual void onLayoutChanged() override {
            Layout->ThemeCheckBox->CheckedChanged.add([this](CheckBox& checkBox) {
                themeTypeChanged(checkBox.Checked ? ThemeType::DARK : ThemeType::LIGHT);
                return true;
            });
            Layout->EnabledCheckBox->CheckedChanged.add([this](CheckBox& checkBox) {
                Layout->Tabs->Enabled = checkBox.Checked;
                repaint();
                return true;
            });

            auto colorClickHandler = [this](Control& control, const MouseClickedEventArgs& args) {
                ColorView* colorView = (ColorView*)control.find(ColorView::TYPE);
                colorChanged(colorView->Color);
                return true;
            };
            Layout->Color1->Clicked.add(colorClickHandler);
            Layout->Color2->Clicked.add(colorClickHandler);
            Layout->Color3->Clicked.add(colorClickHandler);
            Layout->Color4->Clicked.add(colorClickHandler);
        }

    public:
        Event<DemoLayout, Color> colorChanged = *this;
        Event<DemoLayout, ThemeType> themeTypeChanged = *this;
    };
}