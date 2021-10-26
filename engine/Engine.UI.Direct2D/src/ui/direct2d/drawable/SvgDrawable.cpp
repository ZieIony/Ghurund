#include "ghuidxpch.h"
#include "SvgDrawable.h"

namespace Ghurund::UI::Direct2D {
    const Ghurund::Core::Type& SvgDrawable::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<SvgDrawable>(Ghurund::UI::NAMESPACE_NAME, "SvgDrawable")
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
