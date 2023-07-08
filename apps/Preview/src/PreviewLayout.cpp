#include "PreviewLayout.h"

#include "ThemeApplication.h"

namespace Preview {
    void PreviewLayout::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);

        container = (Ghurund::UI::ControlGroup*)find("container");
        color1 = (Ghurund::UI::Button*)find("color1");
        color2 = (Ghurund::UI::Button*)find("color2");
        color3 = (Ghurund::UI::Button*)find("color3");
        color4 = (Ghurund::UI::Button*)find("color4");
        colorTheme = (Ghurund::UI::Button*)find("colorTheme");
        enabledCheckBox = (Ghurund::UI::CheckBox*)find("enabledCheckBox");
        themeCheckBox = (Ghurund::UI::CheckBox*)find("themeCheckBox");

        if (themeCheckBox) {
            themeCheckBox->checkedChanged += [this](CheckBox& checkBox) {
                themeChanged(checkBox.Checked ? ThemeType::DARK : ThemeType::LIGHT);
                repaint();
                return true;
                };
        }
        if (enabledCheckBox) {
            enabledCheckBox->checkedChanged += [this](CheckBox& checkBox) {
                container->Enabled = checkBox.Checked;
                container->repaint();
                return true;
                };
        }

        if (color1) {
            color1->clicked += [this](Button& button, const MouseClickedEventArgs& args) {
                return onColorClicked(args, 0xffd32f2f);
                };
        }
        if (color2) {
            color2->clicked += [this](Button& button, const MouseClickedEventArgs& args) {
                return onColorClicked(args, 0xff1976d2);
                };
        }
        if (color3) {
            color3->clicked += [this](Button& button, const MouseClickedEventArgs& args) {
                return onColorClicked(args, 0xffffa000);
                };
        }
        if (color4) {
            color4->clicked += [this](Button& button, const MouseClickedEventArgs& args) {
                return onColorClicked(args, 0xff388e3c);
                };
        }

        if (colorTheme) {
            auto* colorView = colorTheme->find<ColorView>();
            WindowsTheme::init();
            colorView->Color = ColorValue(WindowsTheme::getAccentColor());
            colorTheme->clicked += [this](Button& button, const MouseClickedEventArgs& args) {
                return onColorClicked(args, WindowsTheme::getAccentColor());
                };
        }
    }
}
