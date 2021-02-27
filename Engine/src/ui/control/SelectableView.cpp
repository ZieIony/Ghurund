#include "SelectableView.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Type& SelectableView::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<SelectableView>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(SelectableView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
