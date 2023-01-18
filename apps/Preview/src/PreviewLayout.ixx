module;

#include "ui/widget/ContentWidget.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/layout/StackLayout.h"
#include "ui/style/WindowsTheme.h"

export module Preview.PreviewLayout;

export namespace Preview {
    using namespace Ghurund::UI;

    enum class ThemeType {
        Dark, Light
    };

    class PreviewLayout:public ControlContainer {
    private:
        Ghurund::UI::StackLayout* container = nullptr;
        Ghurund::UI::Button* color1 = nullptr;
        Ghurund::UI::Button* color2 = nullptr;
        Ghurund::UI::Button* color3 = nullptr;
        Ghurund::UI::Button* color4 = nullptr;
        Ghurund::UI::Button* colorTheme = nullptr;
        Ghurund::UI::CheckBox* enabledCheckBox = nullptr;
        Ghurund::UI::CheckBox* themeCheckBox = nullptr;

    protected:
        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            __super::load(loader, xml);

            container = find<Ghurund::UI::StackLayout>("container");
            color1 = find<Ghurund::UI::Button>("color1");
            color2 = find<Ghurund::UI::Button>("color2");
            color3 = find<Ghurund::UI::Button>("color3");
            color4 = find<Ghurund::UI::Button>("color4");
            colorTheme = find<Ghurund::UI::Button>("colorTheme");
            enabledCheckBox = find<Ghurund::UI::CheckBox>("enabledCheckBox");
            themeCheckBox = find<Ghurund::UI::CheckBox>("themeCheckBox");

            /*themeCheckBox->checkedChanged += [this](CheckBox& checkBox) {
                themeChanged(checkBox.Checked ? ThemeType::Dark : ThemeType::Light);
                repaint();
                return true;
            };
            enabledCheckBox->checkedChanged += [this](CheckBox& checkBox) {
                container->Enabled = checkBox.Checked;
                container->repaint();
                return true;
            };*/

            auto colorClickHandler = [this](Button& button, const MouseClickedEventArgs& args) {
                if (args.Button == MouseButton::LEFT) {
                    ColorView* colorView = (ColorView*)button.find(ColorView::GET_TYPE());
                    Theme->Colors.set(Theme::COLOR_ACCENT, colorView->Color.getValue(*colorView));
                    Theme->updateColors();
                    dispatchThemeChanged();
                } else if (args.Button == MouseButton::RIGHT) {

                }
                return true;
            };
            color1->clicked += colorClickHandler;
            color2->clicked += colorClickHandler;
            color3->clicked += colorClickHandler;
            color4->clicked += colorClickHandler;

            auto* colorView = colorTheme->find<ColorView>();
            WindowsTheme::init();
            colorView->Color = ColorValue(WindowsTheme::getAccentColor());
            colorTheme->clicked += colorClickHandler;
        }

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        Event<PreviewLayout, ThemeType> themeChanged = *this;

        inline StackLayout* getContainer() {
            return container;
        }

        __declspec(property(get = getContainer)) StackLayout* Container;

        void onMeasure(float parentWidth, float parentHeight) {
            __super::onMeasure(parentWidth, parentHeight);
            width->evaluate();
            height->evaluate();
        }

        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Constructor CONSTRUCTOR = Constructor<PreviewLayout>();
            static const Ghurund::Core::Type TYPE = TypeBuilder<PreviewLayout>("Preview", GH_STRINGIFY(PreviewLayout))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }
    };
}