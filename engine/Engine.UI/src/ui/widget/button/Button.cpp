#include "ghuipch.h"
#include "Button.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Button::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Button>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Button>(NAMESPACE_NAME, GH_STRINGIFY(Button))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}