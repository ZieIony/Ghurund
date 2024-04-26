#include "ghuipch.h"
#include "MenuBar.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& MenuBar::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<MenuBar>(NAMESPACE_NAME, GH_STRINGIFY(MenuBar))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
