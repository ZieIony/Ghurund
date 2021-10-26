#pragma once

#include "LayoutBinding.h"
#include "ui/widget/Widget.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/layout/StackLayout.h"
#include "ui/style/WindowsTheme.h"

namespace Preview {
    using namespace Ghurund::UI;

    enum class ThemeType {
        Dark, Light
    };

    class PreviewLayout:public Widget<LayoutBinding> {
    protected:
        virtual void onLayoutChanged() override {
            if (!Layout)
                return;
            Layout->ThemeCheckBox->checkedChanged += [this](CheckBox& checkBox) {
                themeChanged(checkBox.Checked ? ThemeType::Dark : ThemeType::Light);
                repaint();
                return true;
            };
            Layout->EnabledCheckBox->checkedChanged += [this](CheckBox& checkBox) {
                Layout->Container->Enabled = checkBox.Checked;
                Layout->Container->repaint();
                return true;
            };

            auto colorClickHandler = [this](Button& button, const MouseClickedEventArgs& args) {
                if (args.Button == MouseButton::LEFT) {
                    ColorView* colorView = button.find<ColorView>();
                    Theme->Colors.set(Theme::COLOR_ACCENT, colorView->Color.getValue(*colorView));
                    Theme->updateColors();
                    dispatchThemeChanged();
                } else if (args.Button == MouseButton::RIGHT) {

                }
                return true;
            };
            Layout->Color1->clicked += colorClickHandler;
            Layout->Color2->clicked += colorClickHandler;
            Layout->Color3->clicked += colorClickHandler;
            Layout->Color4->clicked += colorClickHandler;

            ColorView* colorView = Layout->ColorTheme->find<ColorView>();
            WindowsTheme::init();
            colorView->Color = ColorValue(WindowsTheme::getAccentColor());
            Layout->ColorTheme->clicked += colorClickHandler;
        }

    public:
        Event<PreviewLayout, ThemeType> themeChanged = *this;

        inline StackLayout* getContainer() {
            return Layout->Container;
        }

        __declspec(property(get = getContainer)) StackLayout* Container;
    };
}