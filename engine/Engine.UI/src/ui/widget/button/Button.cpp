#include "ghuipch.h"
#include "Button.h"

namespace Ghurund::UI {
    void Button::onLayoutChanged() {
        if (clickable) {
            clickable->stateChanged -= stateHandler;
            clickable->clicked -= clickHandler;
            clickable->release();
            clickable = nullptr;
        }
        safeRelease(state);
        __super::onLayoutChanged();
        Control* layoutControl = layout.get();
        if (layoutControl) {
            setPointer(clickable, (Ghurund::UI::ClickableControl*)layoutControl->find("clickable"));
            setPointer(state, (Ghurund::UI::StateIndicator*)layoutControl->find("state"));
            if (clickable) {
                clickable->stateChanged += stateHandler;
                clickable->clicked += clickHandler;
            }
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