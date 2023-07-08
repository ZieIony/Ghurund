#include "ghuipch.h"
#include "Button.h"

namespace Ghurund::UI {
    void Button::bind() {
        __super::bind();
        clickable = (Ghurund::UI::ClickableControl*)ControlContainer::find("clickable");
        state = (Ghurund::UI::StateIndicator*)ControlContainer::find("state");
        if (clickable) {
            clickable->stateChanged += stateHandler;
            clickable->clicked += [this](Control&, const MouseClickedEventArgs& args) {
                return clicked(args);
                };
        }
    }

    const Ghurund::Core::Type& Button::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Button>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Button>(NAMESPACE_NAME, GH_STRINGIFY(Button))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}