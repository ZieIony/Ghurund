#include "ghuipch.h"
#include "SelectableView.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& SelectableView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<SelectableView>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<SelectableView>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(SelectableView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
