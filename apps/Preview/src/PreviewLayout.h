#include <ui/control/ColorView.h>
#include "ui/widget/ContentWidget.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/control/ControlGroup.h"
#include "ui/theme/WindowsTheme.h"
#include "ThemeApplication.h"
#include "../generated/LayoutBinding.h"

namespace Preview {
    using namespace Ghurund::UI;

    class PreviewLayout:public ControlContainer {
    private:
        Bindings::LayoutBinding binding;

    protected:
        virtual void onLoaded() override;

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        Event<PreviewLayout, ThemeType> themeChanged = *this;
        Event<PreviewLayout, uint32_t> colorChanged = *this;

        inline ControlContainer& getContainer() {
            return binding.Container;
        }

        __declspec(property(get = getContainer)) ControlContainer& Container;

        inline bool onColorClicked(const MouseClickedEventArgs& args, uint32_t color) {
            if (args.Button == MouseButton::LEFT) {
                colorChanged(color);
                return true;
            }
            return false;
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