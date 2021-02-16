#include "Button.h"

namespace Ghurund::UI {
    const Ghurund::Type& Button::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Button>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Button))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}