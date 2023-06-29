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

        auto colorClickHandler = [this](Button& button, const MouseClickedEventArgs& args) {
            if (args.Button == MouseButton::LEFT) {
                ColorView* colorView = (ColorView*)button.find(ColorView::GET_TYPE());
                uint32_t color = colorView->Color.getValue(*colorView);
                colorChanged(color);
                dispatchThemeChanged();
            } else if (args.Button == MouseButton::RIGHT) {

            }
            return true;
            };
        if (color1)
            color1->clicked += colorClickHandler;
        if (color2)
            color2->clicked += colorClickHandler;
        if (color3)
            color3->clicked += colorClickHandler;
        if (color4)
            color4->clicked += colorClickHandler;

        if (colorTheme) {
            auto* colorView = colorTheme->find<ColorView>();
            WindowsTheme::init();
            colorView->Color = ColorValue(WindowsTheme::getAccentColor());
            colorTheme->clicked += colorClickHandler;
        }
    }
}
