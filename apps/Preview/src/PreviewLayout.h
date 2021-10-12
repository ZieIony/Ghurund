#pragma once

#include "LayoutBinding.h"
#include "ui/widget/Widget.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/layout/StackLayout.h"

namespace Preview {
    using namespace Ghurund::UI;

    enum class ThemeType {
        Dark, Light
    };

    class PreviewLayout:public Widget<LayoutBinding> {
    private:
        Event<PreviewLayout, ThemeType> themeChanged = *this;

    protected:
        virtual void onLayoutChanged() override {
            if (!Layout)
                return;
            Layout->ThemeCheckBox->CheckedChanged.add([this](CheckBox& checkBox) {
                themeChanged(checkBox.Checked ? ThemeType::Dark : ThemeType::Light);
                repaint();
                return true;
            });
            Layout->EnabledCheckBox->CheckedChanged.add([this](CheckBox& checkBox) {
                Layout->Container->Enabled = checkBox.Checked;
                Layout->Container->repaint();
                return true;
            });

            auto colorClickHandler = [this](Button& button, const MouseClickedEventArgs& args) {
                ColorView* colorView = button.find<ColorView>();
                Theme->Colors.set(Theme::COLOR_ACCENT, colorView->Color.getValue(*colorView));
                Theme->updateColors();
                dispatchThemeChanged();
                return true;
            };
            Layout->Color1->Clicked.add(colorClickHandler);
            Layout->Color2->Clicked.add(colorClickHandler);
            Layout->Color3->Clicked.add(colorClickHandler);
            Layout->Color4->Clicked.add(colorClickHandler);
        }

    public:
        inline Event<PreviewLayout, ThemeType>& getThemeChanged() {
            return themeChanged;
        }

        __declspec(property(get = getThemeChanged)) Event<PreviewLayout, ThemeType>& ThemeChanged;

        inline StackLayout* getContainer() {
            return Layout->Container;
        }

        __declspec(property(get = getContainer)) StackLayout* Container;
    };
}