#include "ui/widget/ContentWidget.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/control/ControlGroup.h"
#include "ui/style/WindowsTheme.h"
#include "ThemeApplication.h"

namespace Preview {
    using namespace Ghurund::UI;

    class PreviewLayout:public ControlContainer {
    private:
        Ghurund::UI::ControlGroup* container = nullptr;
        Ghurund::UI::Button* color1 = nullptr;
        Ghurund::UI::Button* color2 = nullptr;
        Ghurund::UI::Button* color3 = nullptr;
        Ghurund::UI::Button* color4 = nullptr;
        Ghurund::UI::Button* colorTheme = nullptr;
        Ghurund::UI::CheckBox* enabledCheckBox = nullptr;
        Ghurund::UI::CheckBox* themeCheckBox = nullptr;

    protected:
        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        Event<PreviewLayout, ThemeType> themeChanged = *this;
        Event<PreviewLayout, uint32_t> colorChanged = *this;

        inline ControlGroup* getContainer() {
            return container;
        }

        __declspec(property(get = getContainer)) ControlGroup* Container;

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